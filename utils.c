/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 11:24:44 by tle-moel         ###   ########.fr       */
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
int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (!(s1[i] == '\0' && s2[i] == '\0'))
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}