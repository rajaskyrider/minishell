/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:34:00 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/28 17:48:54 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_ms *shell, int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		exit_shell(shell, EXIT_FAILURE);
	}
}

int	create_fork(t_ms *shell)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit_shell(shell, EXIT_FAILURE);
	}
	return (pid);
}