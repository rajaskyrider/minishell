/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/11 15:33:38 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	navigate(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (!ast || !(*ast))
		return ;
	if ((*ast)->token_type == T_AND_IF || (*ast)->token_type == T_OR_IF)
		deal_logical(ast, shell, next_pipe);
	if ((*ast)->left->type == T_OPERATOR)
	{
		setup_pipe(pipe_fd, shell);
		navigate(&(*ast)->left, shell, pipe_fd);
	}
	if ((*ast)->token_type == T_PIPE)
	{
		if (pipe_fd[0] == -1)
			setup_pipe(pipe_fd, shell);
		ms_pipe(*ast, shell, pipe_fd, next_pipe);
	}
}

void	execute_simple(t_ms *shell)
{
	exec_cmd(shell->ast, shell->ast->value, shell, 0);
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
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

void	execute(t_ms *shell)
{
	t_ast 	*ast;
	pid_t	pid;
	int		status;
	int		shellpipe[2];

	ast = shell->ast;
	shellpipe[0] = -1;
	shellpipe[1] = -1;
	if (ast->type == T_OPERATOR)
	{
		navigate(&ast, &shell, shellpipe);
		while ((pid = wait(&status)) > 0)
		{
			if (shell->pid == pid)
			{
				if (WIFEXITED(status))
					shell->lexit_status = WEXITSTATUS(status);
			}
		}
	}
	else
		execute_simple(shell);
	close_fd (shell);
}
