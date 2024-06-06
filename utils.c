/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/06 14:27:08 by tle-moel         ###   ########.fr       */
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
