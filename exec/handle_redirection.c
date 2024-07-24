/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:23:32 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/24 11:35:11 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	less_or_great(t_ms **shell, int *fd, t_io *ptr)
{
	if (ptr->type == T_LESS)
	{
		if ((*shell)->io_in != -1)
			close((*shell)->io_in);
		*fd = open(ptr->value, O_RDONLY);
		if (*fd == -1)
			return (err_mss_heredoc(), 1);
		(*shell)->io_in = *fd;
	}
	if (ptr->type == T_GREAT)
	{
		if ((*shell)->io_out != -1)
			close((*shell)->io_out);
		*fd = open(ptr->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
			return (err_mss_heredoc(), 1);
		(*shell)->io_out = *fd;
	}
	return (0);
}

int	handle_dgreat(t_ms **shell, int *fd, t_io *ptr)
{
	if ((*shell)->io_out != -1)
		close((*shell)->io_out);
	*fd = open(ptr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (err_mss_heredoc(), 1);
	(*shell)->io_out = *fd;
	return (0);
}
