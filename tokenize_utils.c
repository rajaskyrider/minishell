/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:18 by tle-moel          #+#    #+#             */
/*   Updated: 2024/05/21 16:48:31 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
			c == '\r' || c == ' ');
}

int	ms_isoperator(char *s)
{
	if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	if (ft_strncmp(s, "|", 1) == 0)
		return (1);
	if (ft_strncmp(s, "&&", 2) == 0)
		return (1);
	return (0);
}

int	ms_isparenthesis(char c)
{
	if (c == '(' || c == ')')
		return (1);
	return (0);
}

int	ms_isquote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

void	add_token_end_lst(t_token **token_lst, t_token *token)
{
	t_token	*ptr;

	ptr = *token_lst;
	if (*token_lst == NULL)
	{
		*token_lst = token;
		token->next = NULL;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = token;
	token->next = NULL;
}
