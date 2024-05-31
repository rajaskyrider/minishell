/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:25:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/31 09:56:24 by rpandipe         ###   ########.fr       */
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

void	exec_replace(char **new_str, char *start, char *end, char *str, t_ms *sh)
{
	char		*result;
	char		*cmd;
	const char	*env_val;
	int			new_len;

	result = NULL;
	cmd = ft_substr(str, start - str, end - start);
	env_val = getenv(cmd);
	if (env_val)
		result = ft_strdup(env_val);
	else
		result = ft_strdup("");
	new_len = (start - str) + ft_strlen(result) + ft_strlen(end);
	*new_str = ft_calloc(new_len + 1, sizeof(char));
	if (!*new_str)
		exit_shell(sh, EXIT_FAILURE);
	ft_strlcpy(*new_str, str, start - str);
	ft_strlcat(*new_str, result, new_len + 1);
	ft_strlcat(*new_str, end, new_len + 1);
	free (cmd);
	free (result);
}

void	handle_dquote(t_token *ptr, t_ms *shell)
{
	char	*cursor;
	char	*start;
	char	*end;
	char	*new_str;

	cursor = ptr->value;
	start = NULL;
	end = NULL;
	new_str = NULL;
	while (*cursor)
	{
		if (*cursor == '$' && (ft_isalnum(*(cursor + 1)) || *(cursor + 1) == '_'))
		{
			start = cursor;
			cursor++;
			while (ft_isalnum(*cursor) || *cursor == '_')
				cursor++;
			end = cursor;
			exec_replace(&new_str, start, end, ptr->value, shell);
			free (ptr->value);
			ptr->value = new_str;
			cursor = new_str;
		}
		cursor++;
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
	//ft_printf("%s\n", temp->value);
	handle_dquote(temp, shell);
	//ft_printf("%s\n", temp->value);
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

// echo "The date next year will be `date -d \"\`date +'%Y-%m-%d'\` next year\"`"
