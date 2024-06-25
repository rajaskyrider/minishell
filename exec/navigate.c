/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/25 10:14:32 by rpandipe         ###   ########.fr       */
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
	else if ((*ast)->token_type == T_AND_IF)
	{
		ft_printf("Code for AND under construction\n");
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell, pipe_fd);
	}
	else if ((*ast)->token_type == T_OR_IF)
	{
		ft_printf("Code for OR under construction\n");
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell, pipe_fd);
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
}
