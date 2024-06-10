/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/10 09:51:08 by rpandipe         ###   ########.fr       */
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
	/*if (!(ptr && ptr->next && \
					ptr->next->type == T_SINGLE_QUOTE))
		exit_shell(shell, EXIT_FAILURE);*/
	delete_token(token);
	//ptr = ptr->next;
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
	if (shell->token_lst->type == T_SINGLE_QUOTE ||\
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

void	parser(t_ms *shell)
{
	check_cmd(shell);
	//print_token_lst(shell);
	combine_node(shell);
	print_token_lst(shell);
	print_token_lst(shell);
	//deal_io(shell);
	shell->ast = precedence_climbing(shell, &shell->token_lst, 0);
	print_ast(shell->ast, 0);
}

// echo "The date next year will be `date -d \"\`date +'%Y-%m-%d'\` next year\"`"
