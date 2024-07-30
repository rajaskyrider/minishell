/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 08:12:37 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/30 08:19:34 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(int pip[2], t_ms **shell)
{
	if (pipe(pip) == -1)
		print_error(*shell, "Error creating pipe");
}

void	close_pipe(int pip[2])
{
	if (pip[0])
		close(pip[0]);
	if (pip[1])
		close(pip[1]);
}

void	exec_pipeleft(t_ast *ast, t_ms **shell, int pip[2], int next_pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close_pipe(next_pipe);
		dup2(pip[1], STDOUT_FILENO);
		close_pipe(pip);
		exec_cmd(ast, ast->value, *shell, 1);
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)
		print_error(*shell, "Fork failed");
	sync_heredoc(ast, pid, *shell);
}

void	exec_piperight(t_ast *ast, t_ms **shell, int pip[2], int next_pipe[2])
{
	(*shell)->pid = fork();
	if ((*shell)->pid == 0)
	{
		dup2(pip[0], STDIN_FILENO);
		close_pipe(pip);
		if (next_pipe[1] != -1)
		{
			dup2(next_pipe[1], STDOUT_FILENO);
			close_pipe(next_pipe);
		}
		exec_cmd(ast, ast->value, *shell, 1);
		exit (EXIT_FAILURE);
	}
	else if ((*shell)->pid < 0)
		print_error(*shell, "Fork failed");
	sync_heredoc(ast, (*shell)->pid, *shell);
}

void	ms_pipe(t_ast *ast, t_ms **shell, int pipe_fd[2], int next_pipe[2])
{
	if (ast->left->token_type == T_WORD)
		exec_pipeleft(ast->left, shell, pipe_fd, next_pipe);
	close(pipe_fd[1]);
	exec_piperight(ast->right, shell, pipe_fd, next_pipe);
	close(pipe_fd[0]);
}
