/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:57:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 11:17:04 by rpandipe         ###   ########.fr       */
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

void	delete_ast(t_ast **ast)
{
	t_ast	*ptr;

	ptr = *ast;
	if ()
}