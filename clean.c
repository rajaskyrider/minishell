/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:57:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/31 15:22:17 by tle-moel         ###   ########.fr       */
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
	t_token	*current;
	t_token	*next;

	if (!token_lst || !*token_lst)
		return ;
	current = *token_lst;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*token_lst = NULL;
}

void	free_io(t_io *io)
{
	t_io	*ptr;

	while (io)
	{
		free(io->value);
		ptr = io;
		io = io->next;
		free(ptr);
	}
}

void	delete_ast_lst(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	delete_ast_lst(&(*ast)->left);
	delete_ast_lst(&(*ast)->right);
	if ((*ast)->value)
	{
		free((*ast)->value);
		(*ast)->value = NULL;
	}
	if ((*ast)->io)
	{
		free_io((*ast)->io);
	}
	free(*ast);
	*ast = NULL;
}

void	delete_env_lst(t_envlst **environ)
{
	t_envlst	*current;
	t_envlst	*next;

	if (!environ || !*environ)
		return ;
	current = *environ;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		if (current->key)
			free(current->key);
		free(current);
		current = next;
	}
	*environ = NULL;
}
