/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:47:49 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 16:57:08 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_separator(char **cmd_line, t_token **token_lst)
{
	if (ms_isquote(**cmd_line) == 1)
	{
		if (handle_quote(token_lst, cmd_line) == 0)
			return (1);
	}
	else if (ms_isoperator(*cmd_line) == 1)
	{
		if (handle_operator(token_lst, cmd_line) == 0)
			return (1);
	}
	return (0);
}

t_token	*create_token_lst(char *cmd_line, t_ms *shell)
{
	t_token	*token_lst;

	token_lst = NULL;
	while (*cmd_line != '\0')
	{
		while (ms_isspace(*cmd_line) == 1)
			cmd_line++;
		if (quote_separator(&cmd_line, &token_lst) == 1)
			return (shell->error = 1, token_lst);
		else if (ms_isparenthesis(*cmd_line) == 1)
		{
			if (handle_parenthesis(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
		else if (*cmd_line != '\0')
		{
			if (handle_word(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
	}
	return (token_lst);
}

int	tokenize(t_ms *shell)
{
	char	*cmd_line;

	cmd_line = shell->cmd;
	shell->token_lst = create_token_lst(cmd_line, shell);
	if (shell->token_lst == NULL)
		return (0);
	check_syntax_error(shell);
	if (shell->error == 1)
	{
		delete_token_lst(&shell->token_lst);
		shell->error = 0;
		return (0);
	}
	return (1);
}

void	check_syntax_error(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	if (initial_check(ptr, shell) == 1)
		return ;
	while (ptr)
	{
		if (first_check(ptr, shell) == 1)
			return ;
		if (second_check(ptr, shell) == 1)
			return ;
		if (third_check(ptr, shell) == 1)
			return ;
		if (fourth_check(ptr, shell) == 1)
			return ;
		ptr = ptr->next;
	}
}
