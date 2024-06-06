/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:51 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/06 15:27:27 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator(t_token **token_lst, char **cmd_line)
{
	t_token	*token;

	token = NULL;
	if (init_token(token) == 0)
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
	t_token	*token;

	token = NULL;
	if (init_token(token) == 0)
		return (0);
	if (ft_strncmp(*cmd_line, "(", 1) == 0)
		token->type = T_O_PARENT;
	else
		token->type = T_C_PARENT;
	add_token_end_lst(token_lst, token);
	(*cmd_line)++;
	return (1);
}

int	handle_special(t_token **token_lst, char **cmd_line)
{
	t_token	*token;

	token = NULL;
	if (init_token(token) == 0)
		return (0);
	if (ft_strncmp(*cmd_line, "$?", 2) == 0)
		token->type = T_EXIT_STATUS;
	else if (ft_strncmp(*cmd_line, "$", 1) == 0)
		token->type = T_DOLLAR;
	else
		token->type = T_WILDCARD;
	add_token_end_lst(token_lst, token);
	(*cmd_line)++;
	if (token->type == T_EXIT_STATUS)
		(*cmd_line)++;
	return (1);
}

int	handle_word(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	token = NULL;
	if (init_token(token) == 0)
		return (0);
	token->type = T_WORD;
	i = 0;
	while (ms_isspace((*cmd_line)[i]) == 0 && \
			ms_isoperator((*cmd_line) + i) == 0 && \
			ms_isparenthesis((*cmd_line)[i]) == 0 \
			&& ms_isquote((*cmd_line)[i]) == 0 && \
			(*cmd_line)[i] != '$' && \
			(*cmd_line)[i] != '*' && (*cmd_line)[i] != '\0')
		i++;
	token->value = ft_substr(*cmd_line, 0, i);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
	return (1);
}
