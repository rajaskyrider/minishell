/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:44:46 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/01 17:08:45 by tle-moel         ###   ########.fr       */
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

void	just_redirection(t_token **token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return ;
	new->type = T_WORD;
	new->value = ft_strdup("true");
	new->io = NULL;
	new->next = *token;
	if ((*token)->prev)
	{
		new->prev = (*token)->prev;
		(*token)->prev->next = new;
	}
	else
		new->prev = NULL;
	(*token)->prev = new;
	*token = new;
}

void	format_cmd(t_token **token, t_ms *shell)
{
	t_token	*ptr;
	int		count;
	int		flag;

	count = 0;
	flag = 0;
	ptr = *token;
	while (ptr->next)
	{
		if (ptr->type == T_WORD && ptr->next->type == T_WORD)
		{
			flag = 1;
			count++;
			while (ptr->next && ptr->next->type == T_WORD)
			{
				count++;
				ptr = ptr->next;
			}
			break ;
		}
		ptr = ptr->next;
	}
	if (flag == 0)
		return (just_redirection(token));
	*token = setup_reorder(*token, ptr, shell, count);
}

void	check_cmd(t_ms *shell)
{
	t_token	*ptr;
	t_token	*segment_start;

	ptr = shell->token_lst;
	segment_start = ptr;
	if (ms_isredirect(shell->token_lst->type))
		format_cmd(&shell->token_lst, shell);
	while (ptr)
	{
		if (ptr->type == T_PIPE || \
			ptr->type == T_AND_IF || ptr->type == T_OR_IF)
		{
			segment_start = ptr->next;
			if (segment_start)
				if (ms_isredirect(segment_start->type))
					format_cmd(&segment_start, shell);
		}
		ptr = ptr->next;
	}
}
