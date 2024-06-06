/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:47:49 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/06 11:30:21 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token_lst(char *cmd_line)
{
	t_token	*token_lst;

	token_lst = NULL;
	while (*cmd_line != '\0')
	{
		thomas
		while (ms_isspace(*cmd_line) == 1)
			cmd_line++;
		if (ms_isquote(*cmd_line) == 1)
			handle_quote(&token_lst, &cmd_line);
		else if (ms_isoperator(cmd_line) == 1)
			handle_operator(&token_lst, &cmd_line);
		else if (ms_isparenthesis(*cmd_line) == 1)
			handle_parenthesis(&token_lst, &cmd_line);
		else if (*cmd_line == '$' || *cmd_line == '*')
			handle_special(&token_lst, &cmd_line);
		else
			handle_word(&token_lst, &cmd_line);
	}
	return (token_lst);
}

void	tokenize(t_ms *shell)
{
	char	*cmd_line;

	cmd_line = shell->cmd;
	shell->token_lst = create_token_lst(cmd_line);
}
