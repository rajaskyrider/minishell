/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:00:58 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/06 14:58:47 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logical_and(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->left->type == T_OPERATOR)
		navigate(&(*ast)->left, shell, next_pipe);
	else if ((*ast)->left->token_type == T_PARENT)
		ms_subshell((*ast)->left, *shell);
	else
		exec_cmd((*ast)->left, (*ast)->left->value, *shell, 0);
	close_fd (*shell);
	dup2((*shell)->std_in, STDIN_FILENO);
	dup2((*shell)->std_out, STDOUT_FILENO);
	wait(NULL);
	if ((*shell)->lexit_status == 0)
	{
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell, next_pipe);
		else if ((*ast)->right->token_type == T_PARENT)
			ms_subshell((*ast)->right, *shell);
		else
			exec_cmd((*ast)->right, (*ast)->right->value, *shell, 0);
		close_fd (*shell);
	}
}

void	print_shlvl(t_ms *shell)
{
	t_envlst	*ptr;

	ptr = shell->envlst;
	while (ms_strcmp(ptr->key , "SHLVL") != 0)
		ptr = ptr->next;
	dprintf(2, "SHLVL = %s\n", ptr->value);
}

void	deal_operator(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	int	pid;
	int child_pid;
	int	status;
	
	pid = fork();
	if (pid == 0)
	{
		navigate(ast, shell, next_pipe);
		child_pid = wait(&status);
		while (child_pid > 0)
		{
			signal_process();
			if (WIFEXITED(status))
				(*shell)->lexit_status = WEXITSTATUS(status);
			child_pid = wait(&status);
		}
		close_fd (*shell);
		close((*shell)->std_in);
		close((*shell)->std_out);
		exit((*shell)->lexit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*shell)->lexit_status = WEXITSTATUS(status);
}

void	deal_or(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	if ((*ast)->type == T_OPERATOR)
		deal_operator(&(*ast), shell, next_pipe);
	else if ((*ast)->token_type == T_PARENT)
		ms_subshell((*ast), *shell);
	else
		exec_cmd((*ast), (*ast)->value, *shell, 0);
	close_fd (*shell);
}

void	logical_or(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	if (!ast || !(*ast))
		return ;
	deal_or(&(*ast)->left, shell, next_pipe);
	dup2((*shell)->std_in, STDIN_FILENO);
	dup2((*shell)->std_out, STDOUT_FILENO);
	if ((*shell)->lexit_status != 0)
		deal_or(&(*ast)->right, shell, next_pipe);
	else if ((*shell)->lexit_status == 0 && \
		(*ast)->right->token_type == T_AND_IF)
		deal_or(&(*ast)->right->right, shell, next_pipe);

}

void	deal_logical(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	if ((*ast)->token_type == T_AND_IF)
		logical_and(ast, shell, next_pipe);
	else if ((*ast)->token_type == T_OR_IF)
		logical_or(ast, shell, next_pipe);
}
