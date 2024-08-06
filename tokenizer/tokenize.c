/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:47:49 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/06 15:46:34 by rpandipe         ###   ########.fr       */
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
		if (ms_isquote(*cmd_line) == 1 && \
			handle_quote(&token_lst, &cmd_line) == 0)
			return (shell->error = 1, token_lst);
		else if (ms_isoperator(cmd_line) == 1)
		{
			if (handle_operator(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
		else if (ms_isparenthesis(*cmd_line) == 1)
		{
			if (handle_parenthesis(&token_lst, &cmd_line, shell) == 0)
				return (shell->error = 1, token_lst);
		}
		else if (*cmd_line != '\0' && handle_word(&token_lst, &cmd_line) == 0)
			return (shell->error = 1, token_lst);
	}
	return (token_lst);
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
