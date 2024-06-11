/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 11:00:57 by rpandipe         ###   ########.fr       */
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
	while (shell->token_lst)
		delete_token(&shell->token_lst);
	while (shell->ast)
		delete_ast(&shell->ast);
}

void	print_error(t_ms *shell, char *errormsg)
{
	clear_shell(shell);
	perror(errormsg);
}
