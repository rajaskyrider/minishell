/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/13 13:05:58 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	navigate(t_ast **ast, t_ms **shell)
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->left->type == T_OPERATOR)
		navigate(&(*ast)->left, shell);
	if ((*ast)->token_type == T_PIPE)
	{
		ft_printf("Code for pipe under construction\n");
		//exec_pipe(*ast, shell);
	}
	else if ((*ast)->token_type == T_AND_IF)
	{
		ft_printf("Code for AND under construction\n");
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell);
	}
	else if ((*ast)->token_type == T_OR_IF)
	{
		ft_printf("Code for OR under construction\n");
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell);
	}
}

void	execute(t_ms *shell)
{
	t_ast *ast;

	ast = shell->ast;
	if (ast->type == T_OPERATOR)
		navigate(&ast, &shell);
	else
		exec_cmd(shell->ast->value, shell);
}
void	exec_pipe(t_ast *ast, t_ms **shell)
{
	int		new_pip[2];
	pid_t	pid;

	if (pipe(new_pip) == -1)
		exit(EXIT_FAILURE);
	if (ast->left->token_type == T_WORD)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(new_pip[1], STDOUT_FILENO);
			close(new_pip[0]);
			close(new_pip[1]);
			exec_cmd(ast->left->value, *shell);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
	close(new_pip[1]);
	(*shell)->pip[0] = new_pip[0];
	close(new_pip[0]);
	if (pipe(new_pip) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		dup2((*shell)->pip[0], STDIN_FILENO);
		close((*shell)->pip[0]);
		close((*shell)->pip[1]);
		dup2(new_pip[1], STDOUT_FILENO);
		close(new_pip[0]);
		close(new_pip[1]);
		exec_cmd(ast->right->value, *shell);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	close(new_pip[1]);
	(*shell)->pip[0] = new_pip[0];
	close(new_pip[0]);
}
