/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/23 18:13:08 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_single_quote(t_token **token, t_ms *shell)
{
	t_token	*ptr;

	delete_token(token);
	ptr = *token;
	while (ptr && ft_strncmp(ptr->value, "T_SINGLE_QUOTE", \
									ft_strlen(ptr->value))  != 0)
		ptr = ptr->next;
	if (!ptr)
		exit_shell(shell, EXIT_FAILURE);
	delete_token(&ptr);
	(*token) = ptr->prev;
}

void	process_double_quote(t_token **token, t_ms *shell)
{

}

void	process_expr(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	if (ft_strncmp(shell->token_lst->type, "T_SINGLE_QUOTE", \
					ft_strlen(shell->token_lst->type)) == 0 ||\
		ft_strncmp(shell->token_lst->type, "T_DOUBLE_QUOTE", \
					ft_strlen(shell->token_lst->type)) == 0)
		shell->token_lst = shell->token_lst->next;
	while (ptr)
	{
		if (ft_strncmp(ptr->value, "T_SINGLE_QUOTE", \
								ft_strlen(ptr->value))  == 0)
			process_single_quote(&ptr, shell);
		else if (ft_strncmp(ptr->value, "T_DOUBLE_QUOTE", \
								ft_strlen(ptr->value))  == 0)
			process_double_quote(&ptr, shell);
		ptr = ptr->next;
	}
}

void	parser(t_ms *shell)
{
	process_quote(shell);
}