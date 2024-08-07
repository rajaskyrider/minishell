/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:40:20 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/06 15:08:17 by tle-moel         ###   ########.fr       */
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
		return (free(*buffer), NULL);
	(*buffer)[b_read] = '\0';
	while ((*buffer)[i] != '\n')
		i++;
	curr_line = malloc(i + 2);
	if (!curr_line)
		return (free(*buffer), NULL);
	ft_strlcpy(curr_line, *buffer, i + 2);
	free(*buffer);
	*buffer = NULL;
	return (curr_line);
}

void	take_new_line(char **line, char **buffer, t_ms *shell, int tmp_fd)
{
	int	len;

	(*line)[ft_strlen(*line) - 1] = '\0';
	*line = expandcmd(*line, shell);
	len = ft_strlen(*line);
	(*line)[len] = '\n';
	write(tmp_fd, *line, len + 1);
	free(*line);
	ft_putstr_fd("> ", 1);
	*line = read_line(buffer, STDIN_FILENO);
}

void	check_here_doc(char *limiter, int *fd, t_ms *shell)
{
	char	*line;
	char	*buffer;
	int		len;
	int		tmp_fd;

	buffer = NULL;
	tmp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
		return (err_mss_heredoc());
	len = ft_strlen(limiter);
	ft_putstr_fd("> ", 1);
	line = read_line(&buffer, STDIN_FILENO);
	if (line == NULL)
		return ;
	while (!(ft_strncmp(line, limiter, len) == 0 && line[len] == '\n'))
	{
		take_new_line(&line, &buffer, shell, tmp_fd);
		if (line == NULL)
			return ;
	}
	free(line);
	close(tmp_fd);
	*fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (*fd == -1)
		return (err_mss_heredoc());
}

void	set_here_doc(char *limiter, int *fd, t_ms *shell)
{
	int		std_in;
	int		std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	check_here_doc(limiter, fd, shell);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

int	check_redirection(t_ast *ast, t_ms **shell)
{
	int		fd;
	t_io	*ptr;

	(*shell)->io_in = -1;
	(*shell)->io_out = -1;
	ptr = ast->io;
	while (ptr)
	{
		ptr->value = expandcmd(ptr->value, *shell);
		if (less_or_great(shell, &fd, ptr) == 1)
			return (1);
		else if (ptr->type == T_DGREAT)
		{
			if (handle_dgreat(shell, &fd, ptr) == 1)
				return (1);
		}
		else if (ptr->type == T_DLESS)
		{
			if ((*shell)->io_in != -1)
				close((*shell)->io_in);
			set_here_doc(ptr->value, &(*shell)->io_in, *shell);
		}
		ptr = ptr->next;
	}
	return (0);
}
