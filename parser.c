/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/28 17:08:48 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_single_quote(t_token **token, t_ms *shell)
{
	t_token	*ptr;

	ptr = (*token)->next;
	while (ptr && ptr->type != T_SINGLE_QUOTE)
		ptr = ptr->next;
	if (!ptr)
		exit_shell(shell, EXIT_FAILURE);
	/*if (!(ptr && ptr->next && \
					ptr->next->type == T_SINGLE_QUOTE))
		exit_shell(shell, EXIT_FAILURE);*/
	delete_token(token);
	//ptr = ptr->next;
	delete_token(&ptr);
}

void	exec_replace(t_token *ptr, char *start, char *end, char *new_str)
{
	char	*old_str;
	char	*result;
	char	*cmd;
	int		len;

	old_str = ptr->value;
	len = end - start + 1;
	cmd = ft_substr(old_str, (unsigned int)(start - old_str), len);
	free(old_str);
}

char	*dquote_end(char *str, char *start)
{
	char	*end;

	end = NULL;
	if (*start == '\\' && *(start + 1) != '"')
		end = str + 2;
	while (*str && !end)
	{
		if (*start == '$' && !(ft_isalnum(*str) || *str == '_'))
			end = str;
		else if ((*str == '\\' && *(str + 1) == '"'))
			end = str + 2;
		else if (*start == 96 && *str == *start)
			end = str + 1;
		str++;
	}
	return (end);
}

void	handle_dquote(t_token *ptr, t_ms *shell, char *str)
{
	char	*start;
	char	*end;
	char	*new_str;

	start = NULL;
	while(*str)
	{
		if (!start && (*str == 96 || (*str == '\\') || *str == '$'))
		{
			start = str;
			str++;
			end = dquote_end(str, start);
			if (!end)
				exit_shell(shell, EXIT_FAILURE);
			else
			{
				if (str < end)
					handle_dquote(ptr, shell, start + 1);
				exec_replace(ptr, start, end, new_str);
				start = NULL;
				str = end;
			}
		}
		str++;
	}
}

void	process_double_quote(t_token **token, t_ms *shell)
{
	t_token	*ptr;
	t_token	*temp;

	ptr = (*token)->next;
	temp = ptr;
	while (ptr && ptr->type != T_DOUBLE_QUOTE)
		ptr = ptr->next;;
	if (!ptr)
		exit_shell(shell, EXIT_FAILURE);
	delete_token(token);
	delete_token(&ptr);
	handle_dquote(temp, shell, (*token)->value);
	execute_echo(shell, "/bin/echo", (*token)->value);
}

void	process_expr(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	if (shell->token_lst->type == T_SINGLE_QUOTE ||\
		shell->token_lst->type == T_DOUBLE_QUOTE)
		shell->token_lst = shell->token_lst->next;
	while (ptr)
	{
		if (ptr->type == T_SINGLE_QUOTE)
			process_single_quote(&ptr, shell);
		else if (ptr->type == T_DOUBLE_QUOTE)
			process_double_quote(&ptr, shell);
		ptr = ptr->next;
	}
}

void	parser(t_ms *shell)
{
	process_expr(shell);
}