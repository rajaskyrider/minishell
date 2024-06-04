/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:40:34 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/04 10:58:10 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(t_token **token_lst, char **cmd_line)
{
	if (ft_strncmp(*cmd_line, "'", 1) == 0)
	{
		add_quote_token(token_lst, cmd_line);
		handle_single_quote(token_lst, cmd_line);
	}
	else
	{
		add_quote_token(token_lst, cmd_line);
		handle_double_quote(token_lst, cmd_line);
	}
	add_quote_token(token_lst, cmd_line);
}

void	handle_single_quote(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	i = 0;
	while ((*cmd_line)[i] != 34 && (*cmd_line)[i] != '\0')
		i++;
	if ((*cmd_line)[i] != '\0')
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->type = T_WORD;
	token->value = ft_substr(*cmd_line, 0, i);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
}

void	handle_double_quote(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	i = 0;
	while ((*cmd_line)[i] != 39 && (*cmd_line)[i] != '\0')
		i++;
	if ((*cmd_line)[i] != '\0')
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->type = T_WORD;
	token->value = ft_substr(*cmd_line, 0, i);
	process_double_quote(token);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
}

void	process_double_quote(t_token *ptr)
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
}
