/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 08:12:37 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/18 15:41:17 by tle-moel         ###   ########.fr       */
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
	int		status;

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
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*shell)->lexit_status = WEXITSTATUS(status);
}

void	copy_pipe(t_ms **shell, int pip[2])
{
	char	*line;

	close((*shell)->pip[1]);
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
	close((*shell)->pip[0]);
	setup_pipe((*shell)->pip, shell);
	
}

void	exec_piperight(t_ast *ast, t_ms **shell, int pip[2])
{
	pid_t	pid;
	int		status;

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
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*shell)->lexit_status = WEXITSTATUS(status);
}

void	ms_pipe(t_ast *ast, t_ms **shell)
{
	int		pip[2];

	setup_pipe(pip, shell);
	if (ast->left->token_type == T_WORD)
		exec_pipeleft(ast->left, shell, pip);
	else
	{
		ft_putstr_fd("Before copy pipe\n", 2);
		copy_pipe(shell, pip);
		ft_putstr_fd("After copy pipe\n", 2);

	}
	close(pip[1]);
	exec_piperight(ast->right, shell, pip);
	ft_putstr_fd("piperight finished\n", 2);
	close(pip[0]);
}
