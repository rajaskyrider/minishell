/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:44:46 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/07 12:21:36 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reorder_tokens(t_token *dest, t_token *src)
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
}

void	format_cmd(t_token **token)
{
	t_token	*ptr;
	t_token	*new;

	new = NULL;
	ptr = *token;
	while (ptr)
	{
		if (ptr->type == T_WORD && !(ptr->next == NULL \
			|| ptr->next->type == T_LESS \
	 		|| ptr->next->type == T_GREAT \
			|| ptr->next->type == T_DLESS \
			|| ptr->next->type == T_DGREAT))
			break;
		ptr = ptr->next;
	}
	if (!ptr)
	{
		init_token(&new);
		new->type = T_WORD;
		ptr = new;
	}
	reorder_tokens(*token, ptr);
	*token = new;
}

void	check_cmd(t_ms *shell)
{
	if (shell->token_lst->type != T_WORD)
		format_cmd(&shell->token_lst);
}
