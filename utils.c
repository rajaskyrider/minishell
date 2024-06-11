/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 16:58:59 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_token(t_token **token)
{
	*token = (t_token *)malloc(sizeof(t_token));
	if (*token == NULL)
		return (0);
	(*token)->value = NULL;
	(*token)->io = NULL;
	(*token)->next = NULL;
	(*token)->prev = NULL;
	return (1);
}

void	clear_shell(t_ms *shell)
{
	if (shell->cmd)
		free(shell->cmd);
	if (shell->token_lst)
		delete_token(&shell->token_lst);
	if (shell->ast)
		delete_ast_lst(&shell->ast);
	if (shell->environ)
		delete_env_lst(&shell->environ);
}

void	print_error(t_ms *shell, char *errormsg)
{
	clear_shell(shell);
	perror(errormsg);
}
int		ms_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (!(s2[i] == '\0'))
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	if (s1[i] == s2[i] || s1[i] == ' ')
		return (0);
	else
		return (s1[i] - s2[i]);
}