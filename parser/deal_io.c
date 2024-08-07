/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:44:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/01 17:44:19 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_io(t_token *ptr, t_ms *shell)
{
	t_io	*io;
	t_io	*temp;

	io = ft_calloc(sizeof(t_io), 1);
	if (!io)
		exit_shell(shell, EXIT_FAILURE);
	io->type = ptr->next->type;
	io->value = ft_strdup(ptr->next->next->value);
	io->next = NULL;
	io->prev = NULL;
	if (ptr->io)
	{
		temp = ptr->io;
		while (temp->next)
			temp = temp->next;
		temp->next = io;
		io->prev = temp;
	}
	else
		ptr->io = io;
	delete_token(&ptr->next);
	delete_token(&ptr->next);
}

void	logic_heredoc_io(t_token *ptr, t_io *io, t_io *temp)
{
	if (ptr->io)
	{
		temp = ptr->io;
		while (temp->next && temp->next->type == T_DLESS)
			temp = temp->next;
		if (temp->type != T_DLESS)
		{
			temp->next = io;
			io->prev = temp;
		}
		else
		{
			io->next = temp->next;
			io->prev = temp;
			if (temp->next)
				temp->next->prev = io;
			temp->next = io;
		}
	}
	else
		ptr->io = io;
}

void	add_heredoc_io(t_token *ptr, t_ms *shell)
{
	t_io	*io;
	t_io	*temp;

	io = ft_calloc(sizeof(t_io), 1);
	if (!io)
		exit_shell(shell, EXIT_FAILURE);
	io->type = ptr->next->type;
	io->value = ft_strdup(ptr->next->next->value);
	io->next = NULL;
	io->prev = NULL;
	temp = NULL;
	logic_heredoc_io(ptr, io, temp);
	delete_token(&ptr->next);
	delete_token(&ptr->next);
}

void	deal_io(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	while (ptr && ptr->next)
	{
		if (ptr->next->type == T_LESS || ptr->next->type == T_GREAT || \
			ptr->next->type == T_DGREAT)
			create_io(ptr, shell);
		else if (ptr->next->type == T_DLESS)
			add_heredoc_io(ptr, shell);
		else
			ptr = ptr->next;
	}
}
