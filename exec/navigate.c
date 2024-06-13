/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/13 11:01:59 by rpandipe         ###   ########.fr       */
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
/*void	exec_pipe(t_ast *ast, char *cmd, t_ms **shell)
{
	int		pip[2];
	pid_t	pid;

	pipe(pip);
	if ((*shell)->pip)
	{
		dup2(pip[0], STDIN_FILENO);
		dup2(pip[1], STDOUT_FILENO);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pip[0]);
		//dup2(pip[1], STDOUT_FILENO);
		exec_cmd(cmd, *shell);
		close(pip[1]);
		exit;
	}
	close(pip[1]);
	pip[0];
}*/