/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/22 10:00:00 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_single_quote(t_token **token, t_ms *shell)
{
	t_token	*ptr;

	ptr = (*token)->next;
	while (ptr && ptr->type != T_SINGLE_QUOTE)
		ptr = ptr->next;
	if (!ptr)
		exit_shell(shell, EXIT_FAILURE);
	delete_token(token);
	delete_token(&ptr);
}

void	delete_double_quote(t_token **token, t_ms *shell)
{
	t_token	*ptr;

	ptr = (*token)->next;
	while (ptr && ptr->type != T_DOUBLE_QUOTE)
		ptr = ptr->next;
	if (!ptr)
		exit_shell(shell, EXIT_FAILURE);
	delete_token(token);
	delete_token(&ptr);
}

void	process_expr(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	if (shell->token_lst->type == T_SINGLE_QUOTE || \
		shell->token_lst->type == T_DOUBLE_QUOTE)
		shell->token_lst = shell->token_lst->next;
	while (ptr)
	{
		if (ptr->type == T_SINGLE_QUOTE)
			delete_single_quote(&ptr, shell);
		else if (ptr->type == T_DOUBLE_QUOTE)
			delete_double_quote(&ptr, shell);
		ptr = ptr->next;
	}
}

int		parser(t_ms *shell)
{
	t_token	*ptr;

	//print_token_lst(shell);
	check_cmd(shell);
	//ft_putstr_fd("\n----AFTER----\n", 2);
	//print_token_lst(shell);
	deal_io(shell);
	//print_token_lst(shell);
	combine_node(shell);
	//print_token_lst(shell);
	check_reorder(shell);
	ptr = shell->token_lst;
	shell->ast = precedence_climbing(shell, &ptr, 0);
	//print_ast(shell->ast, 0);
	return (1);
}
