/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 11:45:50 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_token(t_token **token)
{
	t_token	*ptr;

	ptr = *token;
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	if (ptr->prev)
		ptr->prev->next = ptr->next;
	if (*token == ptr)
		*token = ptr->next;
	if (ptr->value)
		free(ptr->value);
	free(ptr);
}

void	delete_token_lst(t_token **token_lst)
{
	while (*token_lst)
		delete_token(token_lst);
}

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
	//while (shell->ast)
	//	delete_ast(&shell->ast);
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