/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:00:58 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/03 15:58:01 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logical_and(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->left->type == T_OPERATOR)
		navigate(&(*ast)->left, shell, next_pipe);
	else
		exec_cmd((*ast)->left, (*ast)->left->value, *shell, 0);
	close_fd (*shell);
	if ((*shell)->lexit_status == 0)
	{
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell, next_pipe);
		else
			exec_cmd((*ast)->right, (*ast)->right->value, *shell, 0);
		close_fd (*shell);
	}
}

void	logical_or(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->left->type == T_OPERATOR)
		navigate(&(*ast)->left, shell, next_pipe);
	else
		exec_cmd((*ast)->left, (*ast)->left->value, *shell, 0);
	close_fd (*shell);
	if ((*shell)->lexit_status != 0)
	{
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell, next_pipe);
		else
			exec_cmd((*ast)->right, (*ast)->right->value, *shell, 0);
		close_fd (*shell);
	}
}

void	deal_logical(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	if ((*ast)->token_type == T_AND_IF)
		logical_and(ast, shell, next_pipe);
	else if ((*ast)->token_type == T_OR_IF)
		logical_or(ast, shell, next_pipe);
}