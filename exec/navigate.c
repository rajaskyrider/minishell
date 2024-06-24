/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/21 16:12:30 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line(char **buffer, int std_in)
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

void	navigate(t_ast **ast, t_ms **shell, int last_pipe[2])
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
		ms_pipe(*ast, shell, pipe_fd, last_pipe);
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

void	execute(t_ms *shell)
{
	t_ast *ast;
	//char 	*line;
	pid_t	pid;
	int		status;

	ast = shell->ast;
	if (pipe(shell->pip) == -1)
		print_error(shell, "Error creating pipe");
	if (ast->type == T_OPERATOR)
	{
		navigate(&ast, &shell, (int [2]){STDIN_FILENO, STDOUT_FILENO});
		/*close((shell)->pip[1]);
		line = get_next_line(shell->pip[0]);
		if (line != NULL)
		{
			while (line != NULL)
			{
				write(STDOUT_FILENO, line, ft_strlen(line));
				free(line);
				line = get_next_line(shell->pip[0]);
			}
		}
		close((shell)->pip[0]);*/
		while ((pid = wait(&status)) > 0)
		{
			if (shell->pid == pid)
			{
				if (WIFEXITED(status))
					shell->lexit_status = WEXITSTATUS(status);
			}
		}
		close_pipe(shell->pip);
	}
	else
	{
		close_pipe(shell->pip);
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
}

void	check_redirection(t_ast *ast, t_ms **shell)
{
	int		fd;
	t_io	*ptr;
	
	(*shell)->io_in = -1;
	(*shell)->io_out = -1;
	ptr = ast->io;
	if (ptr)
		ptr->value = expandcmd(ptr->value, *shell);
	while (ptr)
	{
		if (ptr->type == T_LESS)
		{
			fd = open(ptr->value, O_RDONLY);
			if (fd == -1)
			{
				fd = open("/dev/null", O_RDONLY);
			}
			else
				(*shell)->io_in = fd;
		}
		else if (ptr->type == T_GREAT)
		{
			fd = open(ptr->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				exit (EXIT_FAILURE);	
			(*shell)->io_out = fd;

		}
		else if (ptr->type == T_DGREAT)
		{
			fd = open(ptr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				exit (EXIT_FAILURE);
			(*shell)->io_out = fd;
		}
		else if (ptr->type == T_DLESS)
		{
			check_here_doc(ptr->value, 0, (*shell)->io_in);
		}
		ptr = ptr->next;
	}
}
void	check_here_doc(char *limiter, int std_in, int fd_out)
{
	char	*line;
	char	*buffer;
	int		len;

	(void)fd_out;
	buffer = NULL;
	len = ft_strlen(limiter);
	line = read_line(&buffer, std_in);
	if (line == NULL)
		return ;
	while (!(ft_strncmp(line, limiter, len) == 0 && line[len] == '\n'))
	{
		free(line);
		line = read_line(&buffer, std_in);
		if (line == NULL)
			return ;
	}
	free(line);
}


