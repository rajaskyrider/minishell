/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:44:46 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/11 15:03:29 by tle-moel         ###   ########.fr       */
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
	int		flag;

	ft_putstr_fd("Enter format_cmd\n", 2);
	count = 0;
	flag = 1;
	ptr = *token;
	while (ptr->next)
	{
		if (ptr->next->type == T_WORD)
		{
			count += 1;
			flag = 0;
		}
		else if (flag == 0 && ms_isredirect(ptr->next->type))
		{
			flag = 1;
			count = 0;
		}
		else
			break ;
		ptr = ptr->next;
	}
	*token = setup_reorder(*token, ptr, shell, count);
}

void	check_cmd(t_ms *shell)
{
	if (ms_isredirect(shell->token_lst->type))
		format_cmd(&shell->token_lst, shell);
}
