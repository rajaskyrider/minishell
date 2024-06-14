/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thom2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/14 14:14:32 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_ms *shell)
{
	t_ast *ast;

	ast = shell->ast;
	if (ast->type == T_OPERATOR)
		navigate(&ast, &shell);
	else
		exec_cmd(shell->ast->value, shell, 0);
	//print the
}
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
}

void	exec_pipe(t_ast *ast, t_ms **shell)
{
	int		pip[2];
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
}

void	check_redirection(t_ast *ast, t_ms **shell)
{
	int		fd;
	t_io	*ptr;

	/*if (ast->left->io == NULL)
	{
		(*shell)->io_in = -1;
		(*shell)->io_out = -1;
	}*/
	if (ast->left->io != NULL)
	{
		ptr = ast->left->io;
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
					exit;
					(*shell)->io_out = fd;
				}

			}
			else if (ptr->type == T_DGREAT)
			{
				fd = open(ptr->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
				{
					perror("Erro fd out append");
					exit;
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
