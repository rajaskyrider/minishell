/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utokenize_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:51 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 17:13:09 by tle-moel         ###   ########.fr       */
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

int	handle_parenthesis(t_token **token_lst, char **cmd_line)
{
	t_token	*token_open;
	t_token	*token_close;

	token_open = NULL;
	if (init_token(&token_open) == 0)
		return (0);
	if (ft_strncmp(*cmd_line, "(", 1) == 0)
		token_open->type = T_O_PARENT;
	else
		return (0);
	add_token_end_lst(token_lst, token_open);
	(*cmd_line)++;
	handle_subshell(token_lst, cmd_line);
	token_close = NULL;
	if (init_token(&token_close) == 0)
		return (0);
	token_close->type = T_C_PARENT;
	add_token_end_lst(token_lst, token_close);
	(*cmd_line)++;
	return (1);
}

int	handle_subshell(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	i = 0;
	while ((*cmd_line)[i] != ')' && (*cmd_line)[i] != '\0')
		i++;
	if ((*cmd_line)[i] == '\0')
		return (0);
	token = NULL;
	if (init_token(&token) == 0)
		return (0);
	token->type = T_WORD;
	token->value = ft_substr(*cmd_line, 0, i);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
	return (1);
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
	while (ms_isspace((*cmd_line)[i]) == 0 && \
		ms_isparenthesis((*cmd_line)[i]) == 0 && \
		ms_isoperator((*cmd_line) + i) == 0 && (*cmd_line)[i] != '\0')
		i++;
	token->value = ft_substr(*cmd_line, 0, i);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
	return (1);
}
