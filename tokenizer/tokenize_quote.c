/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:40:34 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/21 13:16:49 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	token = NULL;
	if (init_token(&token) == 0)
		return (0);
	token->type = T_WORD;
	i = 0;
	while (ms_isspace((*cmd_line)[i]) == 0 && ms_isparenthesis((*cmd_line)[i]) == 0 && ms_isoperator((*cmd_line) + i) == 0 &&(*cmd_line)[i] != '\0')
	{
		if ((*cmd_line)[i] == '\'')
		{
			if (handle_single_quote(&i, cmd_line) == 0)
				return (0);
		}
		else if ((*cmd_line)[i] == '\"')
		{
			if (handle_double_quote(&i, cmd_line) == 0)
				return (0);
		}
		else
			i++;
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

/*void	process_double_quote(t_token *ptr)
{
	char	*cursor;
	char	*start;
	char	*end;
	char	*new_str;

	cursor = ptr->value;
	start = NULL;
	end = NULL;
	new_str = NULL;
	while (*cursor)
	{
		if (*cursor == '$' && (ft_isalnum(*(cursor + 1)) || *(cursor + 1) == '_'))
		{
			start = cursor;
			cursor ++;
			while (ft_isalnum(*cursor) || *cursor == '_')
				cursor++;
			end = cursor;
			exec_replace(&new_str, start, end, ptr->value);
			free(ptr->value);
			ptr->value = new_str;
			cursor = new_str;
		}
		cursor++;
	}
}

void	exec_replace(char **new_str, char *start, char *end, char *str)
{
	char		*result;
	char		*cmd;
	const char	*env_val;
	int			new_len;

	result = NULL;
	cmd = ft_substr(str, start - str, end - start);
	env_val = getenv(cmd);
	if (env_val)
		result = ft_strdup(env_val);
	else
		result = ft_strdup("");
	new_len = (start - str) + ft_strlen(result) + ft_strlen(end);
	*new_str = ft_calloc(new_len + 1, sizeof(char));
	if (!*new_str)
		return ;
	ft_strlcpy(*new_str, str, start - str);
	ft_strlcat(*new_str, result, new_len + 1);
	ft_strlcat(*new_str, end, new_len + 1);
	free(cmd);
	free(result);
}

void	add_quote_token(t_token **token_lst, char **cmd_line)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->value = NULL;
	if (ft_strncmp(*cmd_line, "'", 1) == 0)
		token->type = T_SINGLE_QUOTE;
	else
		token->type = T_DOUBLE_QUOTE;
	add_token_end_lst(token_lst, token);
	(*cmd_line)++;
}*/
