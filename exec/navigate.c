/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/30 09:46:23 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	navigate(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (!ast || !(*ast))
		return ;
	if ((*ast)->token_type == T_AND_IF || (*ast)->token_type == T_OR_IF)
		deal_logical(ast, shell, next_pipe);
	else if ((*ast)->left->type == T_OPERATOR)
	{
		setup_pipe(pipe_fd, shell);
		navigate(&(*ast)->left, shell, pipe_fd);
	}
	if ((*ast)->token_type == T_PIPE)
	{
		if (pipe_fd[0] == -1)
			setup_pipe(pipe_fd, shell);
		ms_pipe(*ast, shell, pipe_fd, next_pipe);
	}
	else if ((*ast)->token_type == T_PARENT)
		ms_subshell(*ast, *shell);
}

void	execute_simple(t_ms *shell)
{
	exec_cmd(shell->ast, shell->ast->value, shell, 0);
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	if (shell->io_in != -1)
	{
		close(shell->io_in);
		shell->io_in = -1;
	}
	if (shell->io_out != -1)
	{
		close(shell->io_out);
		shell->io_out = -1;
	}
}

void	set_execute(int *pip0, int *pip1)
{
	*pip0 = -1;
	*pip1 = -1;
}

void	execute(t_ms *shell)
{
	t_ast	*ast;
	pid_t	pid;
	int		status;
	int		shellpipe[2];

	ast = shell->ast;
	set_execute(&(shellpipe[0]), &(shellpipe[1]));
	if (ast->type == T_OPERATOR)
	{
		navigate(&ast, &shell, shellpipe);
		pid = wait(&status);
		while (pid > 0)
		{
			signal_process();
			if (shell->pid == pid)
				if (WIFEXITED(status))
					shell->lexit_status = WEXITSTATUS(status);
			pid = wait(&status);
		}
	}
	else if (ast->token_type == T_PARENT)
		ms_subshell(ast, shell);
	else
		execute_simple(shell);
	close_fd (shell);
}
