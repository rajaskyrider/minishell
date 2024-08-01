/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:40:34 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/01 14:40:21 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_condition(int *i, char **cmd_line)
{
	if ((*cmd_line)[*i] == '\'')
	{
		if (handle_single_quote(i, cmd_line) == 0)
			return (0);
	}
	else if ((*cmd_line)[*i] == '\"')
	{
		if (handle_double_quote(i, cmd_line) == 0)
			return (0);
	}
	else
		(*i)++;
	return (1);
}

int	handle_quote(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	token = NULL;
	if (init_token(&token) == 0)
		return (0);
	token->type = T_WORD;
	i = 0;
	while (ms_isspace((*cmd_line)[i]) == 0 && \
		ms_isparenthesis((*cmd_line)[i]) == 0 && \
		ms_isoperator((*cmd_line) + i) == 0 && (*cmd_line)[i] != '\0')
	{
		if (quote_condition(&i, cmd_line) == 0)
		{
			free(token);
			return (0);
		}
	}
	token->value = ft_substr(*cmd_line, 0, i);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
	return (1);
}

int	handle_single_quote(int	*i, char **cmd_line)
{
	(*i)++;
	while ((*cmd_line)[*i] != 39 && (*cmd_line)[*i] != '\0')
		(*i)++;
	if ((*cmd_line)[*i] == '\0')
		return (0);
	(*i)++;
	return (1);
}

int	handle_double_quote(int *i, char **cmd_line)
{
	(*i)++;
	while ((*cmd_line)[*i] != 34 && (*cmd_line)[*i] != '\0')
		(*i)++;
	if ((*cmd_line)[*i] == '\0')
		return (0);
	(*i)++;
	return (1);
}
