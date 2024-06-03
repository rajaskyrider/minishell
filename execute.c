/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:47:16 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/03 10:23:05 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(t_ms *shell, char *cmd, char *args[3])
{
	pid_t	pid;
	int		bytes_read;
	char	buffer[1024];
	int		pipefd[2];

	create_pipe(shell, pipefd);
	pid = create_fork(shell);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd, args, NULL);
		perror("execve");
		exit_shell(shell, EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
		if (bytes_read > 0)
			buffer[bytes_read] = 0;
		close(pipefd[0]);
	}
}
