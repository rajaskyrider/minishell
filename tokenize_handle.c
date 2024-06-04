/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:51 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/04 10:53:07 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_operator(t_token **token_lst, char **cmd_line)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->value = NULL;
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
	if (token->type != T_LESS || token->type != T_GREAT || \
		token->type != T_PIPE)
		(*cmd_line)++;
	(*cmd_line)++;
}

void	handle_parenthesis(t_token **token_lst, char **cmd_line)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->value = NULL;
	if (ft_strncmp(*cmd_line, "(", 1) == 0)
		token->type = T_O_PARENT;
	else
		token->type = T_C_PARENT;
	add_token_end_lst(token_lst, token);
	(*cmd_line)++;
}

void	handle_special(t_token **token_lst, char **cmd_line)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->value = NULL;
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
}

void	handle_word(t_token **token_lst, char **cmd_line)
{
	t_token	*token;
	int		i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return ;
	token->type = T_WORD;
	i = 0;
	while (ms_isspace((*cmd_line)[i]) == 0 && \
			ms_isoperator((*cmd_line)) == 0 && \
			ms_isparenthesis((*cmd_line)[i]) == 0 \
			&& ms_isquote((*cmd_line)[i]) == 0 && \
			(*cmd_line)[i] != '$' && \
			(*cmd_line)[i] != '*' && (*cmd_line)[i] != '\0')
		i++;
	token->value = ft_substr(*cmd_line, 0, i);
	add_token_end_lst(token_lst, token);
	(*cmd_line) += i;
}
