/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:47:49 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/17 09:40:14 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token_lst(char *cmd_line, t_ms *shell)
{
	t_token	*token_lst;

	token_lst = NULL;
	while (*cmd_line != '\0')
	{
		while (ms_isspace(*cmd_line) == 1)
			cmd_line++;
		if (ms_isquote(*cmd_line) == 1)
		{
			if (handle_quote(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
		else if (ms_isoperator(cmd_line) == 1)
		{
			if (handle_operator(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
		else if (ms_isparenthesis(*cmd_line) == 1)
		{
			if (handle_parenthesis(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
		else
		{
			if (handle_word(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
	}
	return (token_lst);
}

void	tokenize(t_ms *shell)
{
	char	*cmd_line;

	cmd_line = shell->cmd;
	shell->token_lst = create_token_lst(cmd_line, shell);
	if (shell->error == 1)
		delete_token_lst(&shell->token_lst);
}
