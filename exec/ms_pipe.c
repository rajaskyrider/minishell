/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 08:12:37 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/14 14:41:41 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(int pip[2], t_ms **shell)
{
	if (pipe(pip) == -1)
		print_error(*shell, "Error creating pipe");
}

void	close_pipe(int pip1[2])
{
	close(pip1[0]);
	close(pip1[1]);
}

void	exec_pipeleft(t_ast *ast, t_ms **shell, int pip[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2((*shell)->pip[0], STDIN_FILENO);
		if (ast->left->io)
			check_redirection(ast->left, shell);
		else
			dup2(pip[1], STDOUT_FILENO);
		close_pipe(pip);
		close_pipe((*shell)->pip);
		exec_cmd(ast->left->value, *shell, 1);
		exit (EXIT_SUCCESS);
	}
	else if (pid < 0)
		print_error(*shell, "Fork failed");
	waitpid(pid, NULL, 0);
}

void	copy_pipe(t_ms **shell, int pip[2])
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid == 0)
	{
		dup2(pip[1], STDOUT_FILENO);
		close_pipe(pip);
		line = get_next_line((*shell)->pip[0]);
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
		close_pipe((*shell)->pip);
		exit (EXIT_SUCCESS);
	}
	else if (pid < 0)
		print_error(*shell, "Fork failed");
	waitpid(pid, NULL, 0);	
	close_pipe((*shell)->pip);
	setup_pipe((*shell)->pip, shell);
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
		if (ast->right->io)
			check_redirection(ast->right, shell);
		close_pipe((*shell)->pip);
		exec_cmd(ast->right->value, *shell, 1);
		exit (EXIT_SUCCESS);
	}
	else if (pid < 0)
		print_error(*shell, "Fork failed");
	waitpid(pid, NULL, 0);
}

void	ms_pipe(t_ast *ast, t_ms **shell)
{
	int		pip[2];

	setup_pipe(pip, shell);
	if (ast->left->type == T_OPERAND)
		exec_pipeleft(ast, shell, pip);
	else
	{
		copy_pipe(shell, pip);
	}
	close(pip[1]);
	exec_piperight(ast, shell, pip);
	close_pipe(pip);
}
