/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/12 10:48:30 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	navigate(t_ast **ast, t_ms *shell)
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->left->type == T_OPERATOR)
		navigate(&(*ast)->left, shell);
	if ((*ast)->right->type == T_OPERATOR)
		navigate(&(*ast)->right, shell);
	if (ms_isredirect((*ast)->token_type) == 1)
		redirect(shell, *ast);
	else if ((*ast)->token_type == T_PIPE)
		ft_printf("Code for pipe under construction\n");
	else if ((*ast)->token_type == T_AND_IF)
		ft_printf("Code for AND under construction\n");
	else if ((*ast)->token_type == T_OR_IF)
		ft_printf("Code for OR under construction\n");
}

void	execute(t_ms *shell)
{
	t_ast *ast;

	ast = shell->ast;
	if (ast->type == T_OPERATOR)
		navigate(&ast, shell);
	else
		exec_cmd(shell->ast->value, shell);
}
