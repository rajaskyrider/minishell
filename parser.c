/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/27 18:40:15 by rpandipe         ###   ########.fr       */
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

void	handle_dquote(t_token *ptr, t_ms *shell)
{
	char	*str;
	char	*start;
	char	*end;

	str = ptr->value;
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
			break ;
		}
		str++;
	}
	exec_replace(ptr, start, end);
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
	handle_dquote(temp, shell);
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