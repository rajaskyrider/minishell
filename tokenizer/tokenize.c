/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:47:49 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 14:44:01 by tle-moel         ###   ########.fr       */
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
		else if (*cmd_line != '\0')
		{
			if (handle_word(&token_lst, &cmd_line) == 0)
				return (shell->error = 1, token_lst);
		}
	}
	return (token_lst);
}

void	check_syntax_error(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	if (ptr && ptr->type == T_WORD && ptr->value[0] == '*')
	{
		shell->error = 1;
		shell->lexit_status = 127;
		ft_putstr_fd("minishell: command not found\n", 2);
		return ;
	}
	else if (ptr && (ptr->type == T_AND_IF || ptr->type == T_OR_IF || ptr->type == T_PIPE))
	{
		shell->error = 1;
		shell->lexit_status = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return ;
	}
	while (ptr)
	{
		if (ptr->type == T_AND_IF || ptr->type == T_OR_IF || ptr->type == T_PIPE)
		{
			if (!ptr->next || ptr->next->type == T_AND_IF || ptr->next->type == T_OR_IF || ptr->next->type == T_PIPE)
			{
				shell->error = 1;
				shell->lexit_status = 2;
				ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
				return ;
			}
		}
		if (ptr->type == T_GREAT || ptr->type == T_DGREAT || ptr->type == T_LESS || ptr->type == T_DLESS)
		{
			if (!ptr->next || ptr->next->type == T_AND_IF || ptr->next->type == T_OR_IF || ptr->next->type == T_PIPE || ptr->next->type == T_GREAT || ptr->next->type == T_DGREAT || ptr->next->type == T_LESS || ptr->next->type == T_DLESS)
			{
				shell->error = 1;
				shell->lexit_status = 2;
				ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
				return ;
			}
		}
		if (ptr->next && (ptr->type == T_GREAT || ptr->type == T_DGREAT || ptr->type == T_LESS))
		{
			if (ptr->next->type == T_WORD && ptr->next->value[0] == '*' && ptr->next->value[1] == '\0')
			{
				shell->error = 1;
				shell->lexit_status = 1;
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				return ;
			}
		}
		if (ptr->next && ptr->type == T_DLESS)
		{
			if (ptr->next->type == T_WORD && ptr->next->value[0] == '*' && ptr->next->value[1] == '\0')
			{
				shell->error = 1;
				shell->lexit_status = 0;
				ft_putstr_fd("minishell: here-document at line 1 delimited by end-of-file (wanted `*\')\n", 2);
				return ;
			}
		}
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
