/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:12:45 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/30 09:41:43 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_ms *shell)
{
	if (shell->io_in != -1)
	{
		close(shell->io_in);
		shell->io_in = -1;
	}
	if (shell->io_out != -1)
	{
		close(shell->io_out);
		shell->io_out = -1;
	}
}

void	err_mss_heredoc(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	sync_heredoc(t_ast *ast, int pid, t_ms *shell)
{
	t_io	*ptr;
	int		status;

	ptr = ast->io;
	while (ptr)
	{
		if (ptr->type == T_DLESS)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				shell->lexit_status = WIFEXITED(status);
			break ;
		}
		ptr = ptr->next;
	}
}
