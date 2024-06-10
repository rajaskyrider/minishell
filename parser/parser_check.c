/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:44:46 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/10 10:47:57 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*reorder_tokens(t_token *dest, t_token *src)
{
	if (src->prev)
		src->prev->next = src->next;
	if (src->next)
		src->next->prev = src->prev;
	src->prev = dest->prev;
	src->next = dest;
	if (dest->prev)
		dest->prev->next = src;
	dest->prev = src;
	return (src);
}

t_token	*setup_reorder(t_token *token, t_token *ptr, t_ms *shell, int count)
{
	t_token	*new;

	new = NULL;
	if (count == 0)
		print_error(shell, "Syntax error\n");
	else if (count == 1)
	{
		init_token(&new);
		new->type = T_WORD;
		ptr = new;
		new = reorder_tokens(token, ptr);
	}
	else if (count == 2)
		new = reorder_tokens(token, ptr);
	else if (count >= 3)
	{
		while (count-- >= 3)
		{
			ptr = ptr->prev;
			concat_node(ptr, shell);
		}
		new = reorder_tokens(token, ptr);
	}
	return (new);
}

void	format_cmd(t_token **token, t_ms *shell)
{
	t_token	*ptr;

	int		count;

	count = 0;
	ptr = *token;
	while (ptr->next)
	{
		if (ptr->next->type != T_WORD)
			break;
		count += 1;
		ptr = ptr->next;
	}
	*token = setup_reorder(*token, ptr, shell, count);
}

void	check_cmd(t_ms *shell)
{
	if (shell->token_lst->type != T_WORD)
	{
		if (shell->token_lst->type== T_LESS \
	 		|| shell->token_lst->type == T_GREAT \
			|| shell->token_lst->type == T_DLESS \
			|| shell->token_lst->type == T_DGREAT)
			format_cmd(&shell->token_lst, shell);
		else
			print_error(shell, "Syntax error\n");
	}
}
