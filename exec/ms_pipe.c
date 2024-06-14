/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 08:12:37 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/14 16:27:24 by tle-moel         ###   ########.fr       */
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

void	exec_pipeleft(t_ast *ast, t_ms **shell, int pip[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pip[1], STDOUT_FILENO);
		if (ast->io)
		{
			check_redirection(ast, shell);
			if ((*shell)->io_in != -1)
				dup2((*shell)->io_in, STDIN_FILENO);
			if ((*shell)->io_out != -1)
				dup2((*shell)->io_out, STDOUT_FILENO);
		}
		close_pipe(pip);
		close_pipe((*shell)->pip);
		exec_cmd(ast->value, *shell, 1);
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)
		print_error(*shell, "Fork failed");
	waitpid(pid, NULL, 0);
}

void	copy_pipe(t_ms **shell, int pip[2])
{
	char	*line;

	line = get_next_line((*shell)->pip[0]);
	if (line != NULL)
	{
		while (line != NULL)
		{
			write(pip[1], line, ft_strlen(line));
			free(line);
			line = get_next_line((*shell)->pip[0]);
		}
	}
	else
		dup2(STDIN_FILENO, pip[0]);
}

void	exec_piperight(t_ast *ast, t_ms **shell, int pip[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pip[0], STDIN_FILENO);
		close_pipe(pip);
		dup2((*shell)->pip[1], STDOUT_FILENO);
		if (ast->io)
		{
			check_redirection(ast, shell);
			if ((*shell)->io_in != -1)
				dup2((*shell)->io_in, STDIN_FILENO);
			if ((*shell)->io_out != -1)
				dup2((*shell)->io_out, STDOUT_FILENO);
		}
		close_pipe((*shell)->pip);
		exec_cmd(ast->value, *shell, 1);
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)
		print_error(*shell, "Fork failed");
	waitpid(pid, NULL, 0);
}

void	ms_pipe(t_ast *ast, t_ms **shell)
{
	int		pip[2];

	setup_pipe(pip, shell);
	if (ast->left->token_type == T_WORD)
		exec_pipeleft(ast->left, shell, pip);
	else
		copy_pipe(shell, pip);
	close(pip[1]);
	exec_piperight(ast->right, shell, pip);
	close_pipe(pip);
}