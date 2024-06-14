/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thomas_navigate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/14 10:11:00 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_node(t_ast **ast, t_ms **shell, int *fd_in, int *fd_out)
{
	//printf("Enter execute node\n");
	if ((*ast)->token_type == T_WORD)
	{
		//printf("Node is a T_WORD\n");
		if ((*ast)->io != NULL)
		{
			printf("There is some redirection to check\n");
			check_redirection(*ast, shell);
			if ((*shell)->io_in != -1)
			{
				dup2((*shell)->io_in, STDIN_FILENO);
				close((*shell)->io_in);
			}
			if ((*shell)->io_out != -1)
			{
				dup2((*shell)->io_out, STDOUT_FILENO);
				close((*shell)->io_out);
			}
		}
		//printf("I've checked the redirection\n");
		exec_cmd((*ast)->value, *shell);
		exit(EXIT_FAILURE);
	}
	else if ((*ast)->token_type == T_PIPE)
	{
		//printf("Node is a T_PIPE\n");
		int		status;
		int		pip[2];
		pid_t	pid;

		pipe(pip);
		pid = fork();
		if (pid == 0)
		{
			close(pip[0]);
			dup2(pip[1], STDOUT_FILENO);
			close(pip[1]);
			execute_node(&(*ast)->left, shell, fd_in, fd_out);
		}
		close(pip[1]);
		dup2(pip[0], STDIN_FILENO);
		close(pip[0]);
		execute_node(&(*ast)->right, shell, fd_in, fd_out);
		waitpid(pid, &status, 0);
	}
	/*
	else if ((*ast)->token_type == T_AND_IF)
	{
		execute_node(&(*ast)->left, shell, fd_in, fd_out);
		if (WEXITSTATUS(status) == 0)
			execute_node(&(*ast)->right, shell, fd_in, fd_out);
	}
	else if ((*ast)->token_type == T_OR_IF)
	{
		execute_node(&(*ast)->left, shell, fd_in, fd_out);
		if (WEXITSTATUS(status) != 0)
			execute_node(&(*ast)->right, shell, fd_in, fd_out);
	}
	*/
	return ;
}
void	execute(t_ms *shell)
{
	t_ast	*ast;
	int		fd_in;
	int		fd_out;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	ast = shell->ast;
	if (!ast)
		return ;
	if (ast->type == T_OPERATOR)
		execute_node(&ast, &shell, &fd_in, &fd_out);
	else
		exec_cmd(shell->ast->value, shell);
}
/*
void	navigate(t_ast **ast, t_ms **shell)
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->left->type == T_OPERATOR)
		navigate(&(*ast)->left, shell);
	if ((*ast)->token_type == T_PIPE)
	{
		ft_printf("Code for pipe under construction\n");
		exec_pipe(*ast, shell);
	}
	else if ((*ast)->token_type == T_AND_IF)
	{
		ft_printf("Code for AND under construction\n");
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell);
	}
	else if ((*ast)->token_type == T_OR_IF)
	{
		ft_printf("Code for OR under construction\n");
		if ((*ast)->right->type == T_OPERATOR)
			navigate(&(*ast)->right, shell);
	}
}*/
/*
void	execute(t_ms *shell)
{
	t_ast *ast;

	ast = shell->ast;
	if (ast->type == T_OPERATOR)
		navigate(&ast, &shell);
	else
		exec_cmd(shell->ast->value, shell);
	//print the result
}*/
/*void	exec_pipe(t_ast *ast, t_ms **shell)
{
	int		new_pip[2];
	pid_t	pid;

	if (pipe(new_pip) == -1)
		exit(EXIT_FAILURE);
	if (ast->left->token_type == T_WORD)
		exec_left_pipe(ast, shell, &new_pip);

	close(new_pip[1]);
	(*shell)->pip[0] = new_pip[0];
	close(new_pip[0]);

	if (pipe(new_pip) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		dup2((*shell)->pip[0], STDIN_FILENO);
		close((*shell)->pip[0]);
		close((*shell)->pip[1]);
		dup2(new_pip[1], STDOUT_FILENO);
		close(new_pip[0]);
		close(new_pip[1]);
		exec_cmd(ast->right->value, *shell);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	close(new_pip[1]);
	(*shell)->pip[0] = new_pip[0];
	close(new_pip[0]);
}
void	exec_left_pipe(t_ast *ast, t_ms **shell, int (*new_pip)[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(new_pip[1], STDOUT_FILENO);
		close(new_pip[0]);
		close(new_pip[1]);
		check_redirection(ast, shell);
		if ((*shell)->io_in != -1)
			dup2((*shell)->io_in, STDIN_FILENO);
		if ((*shell)->io_out != -1)
			dup2((*shell)->io_out, STDOUT_FILENO);
		exec_cmd(ast->left->value, *shell);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
}*/

void	check_redirection(t_ast *ast, t_ms **shell)
{
	printf("Enter check redirection\n");
	int		fd;
	t_io	*ptr;

	/*if (ast->left->io == NULL)
	{
		(*shell)->io_in = -1;
		(*shell)->io_out = -1;
	}*/
	if (ast->io != NULL)
	{
		ptr = ast->io;
		while (ptr)
		{
			if (ptr->type == T_LESS)
			{
				fd = open(ptr->next->value, O_RDONLY);
				if (fd == -1)
				{
					perror("Error fd in");
					fd = open("/dev/null", O_RDONLY);
					(*shell)->io_in = fd;
				}
			}
			else if (ptr->type == T_GREAT)
			{
				fd = open(ptr->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					perror("Error fd out");
					exit(EXIT_FAILURE);
					(*shell)->io_out = fd;
				}

			}
			else if (ptr->type == T_DGREAT)
			{
				fd = open(ptr->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
				{
					perror("Erro fd out append");
					exit(EXIT_FAILURE); 
					(*shell)->io_out = fd;
				}
			}
			else if (ptr->type == T_DLESS)
				check_here_doc(ptr->next->value, 0, (*shell)->io_in);
			ptr = ptr->next;
		}
	}
}
void	check_here_doc(char *limiter, int std_in, int fd_out)
{
	char	*line;
	char	*buffer;
	int		len;

	buffer = NULL;
	len = ft_strlen(limiter);
	line = read_line(&buffer, std_in);
	if (line == NULL)
		return ;
	while (!(ft_strncmp(line, limiter, len) == 0 && line[len] == '\n'))
	{
		ft_putstr_fd(line, fd_out);
		free(line);
		line = read_line(&buffer, std_in);
		if (line == NULL)
			return ;
	}
	free(line);
}

char	*read_line(char **buffer, int std_in)
{
	int		i;
	int		b_read;
	char	*curr_line;

	i = 0;
	*buffer = malloc(BUFFER_SIZE + 1);
	if (*buffer == NULL)
		return (NULL);
	b_read = read(std_in, *buffer, BUFFER_SIZE);
	if (b_read <= 0)
	{
		free(*buffer);
		return (NULL);
	}
	(*buffer)[b_read] = '\0';
	while ((*buffer)[i] != '\n')
		i++;
	curr_line = malloc(i + 2);
	if (curr_line)
	{
		free(*buffer);
		return (NULL);
	}
	ft_strlcpy(curr_line, *buffer, i + 2);
	free(*buffer);
	*buffer = NULL;
	return (curr_line);
}
