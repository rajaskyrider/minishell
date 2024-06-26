/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:44:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/17 11:15:58 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_io(t_token *ptr, t_ms *shell)
{
	t_io	*io;

	io = ft_calloc(sizeof(t_io), 1);
	if (!io)
		exit_shell(shell, EXIT_FAILURE);
	io->type = ptr->next->type;
	io->value = ft_strdup(ptr->next->next->value);
	io->next = NULL;
	io->prev = NULL;
	if (ptr->io)
	{
		while (ptr->io->next)
			ptr->io = ptr->io->next;
		ptr->io->next = io;
		io->prev = ptr->io;
	}
	else
		ptr->io = io;
	delete_token(&ptr->next);
	delete_token(&ptr->next);
}

void	deal_io(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	while (ptr && ptr->next)
	{
		if (ptr->next->type == T_LESS || ptr->next->type == T_GREAT || ptr->next->type == T_DLESS \
								|| ptr->next->type == T_DGREAT)
			create_io(ptr, shell);
		else
			ptr = ptr->next;
	}
}