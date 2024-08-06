/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:51 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/06 15:45:31 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator(t_token **token_lst, char **cmd_line)
{
	t_token	*token;

	token = NULL;
	if (init_token(&token) == 0)
		return (0);
	if (ft_strncmp(*cmd_line, "&&", 2) == 0)
		token->type = T_AND_IF;
	else if (ft_strncmp(*cmd_line, "||", 2) == 0)
		token->type = T_OR_IF;
	else if (ft_strncmp(*cmd_line, "<<", 2) == 0)
		token->type = T_DLESS;
	else if (ft_strncmp(*cmd_line, ">>", 2) == 0)
		token->type = T_DGREAT;
	else if (ft_strncmp(*cmd_line, "<", 1) == 0)
		token->type = T_LESS;
	else if (ft_strncmp(*cmd_line, ">", 1) == 0)
		token->type = T_GREAT;
	else if (ft_strncmp(*cmd_line, "|", 1) == 0)
		token->type = T_PIPE;
	add_token_end_lst(token_lst, token);
	if (token->type != T_LESS && token->type != T_GREAT && \
		token->type != T_PIPE)
		(*cmd_line)++;
	(*cmd_line)++;
	return (1);
}

int	handle_parenthesis(t_token **token_lst, char **cmd_line, t_ms *shell)
{
	t_token	*token;

	token = NULL;
	if (ft_strncmp(*cmd_line, ")", 1) == 0)
	{
		shell->lexit_status = 2;
		ft_putstr_fd("minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token\n", 2);
		return (0);
	}
	(*cmd_line)++;
	if (init_token(&token) == 0)
		return (0);
	token->type = T_PARENT;
	token->value = handle_subshell(token_lst, cmd_line);
	if (!token->value)
		return (0);
	add_token_end_lst(token_lst, token);
	(*cmd_line)++;
	return (1);
}

char	*handle_subshell(t_token **token_lst, char **cmd_line)
{
	char	*value;
	int		i;
	int		count;

	(void)token_lst;
	i = 0;
	count = 1;
	while (count != 0 && (*cmd_line)[i] != '\0')
	{
		if ((*cmd_line)[i] == ')')
			count--;
		if ((*cmd_line)[i] == '(')
			count++;
		i++;
	}
	i--;
	if ((*cmd_line)[i] == '\0')
		return (NULL);
	value = ft_substr(*cmd_line, 0, i);
	(*cmd_line) += i;
	return (value);
}

int	handle_word(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	token = NULL;
	if (init_token(&token) == 0)
		return (0);
	token->type = T_WORD;
	i = 0;
	while (!ms_isspace((*cmd_line)[i]) && !ms_isparenthesis((*cmd_line)[i]) && \
		!ms_isoperator((*cmd_line) + i) && (*cmd_line)[i] != '\0')
	{
		if (ms_isquote((*cmd_line)[i]) == 1)
		{
			while ((*cmd_line)[++i] && ms_isquote((*cmd_line)[i]) == 0)
			{
				if (!(*cmd_line)[i])
					return (0);
			}
		}
		i++;
	}
	token->value = ft_substr(*cmd_line, 0, i);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
	return (1);
}
