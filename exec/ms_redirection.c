/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:40:20 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/15 17:13:09 by tle-moel         ###   ########.fr       */
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
	if (!curr_line)
	{
		free(*buffer);
		return (NULL);
	}
	ft_strlcpy(curr_line, *buffer, i + 2);
	free(*buffer);
	*buffer = NULL;
	return (curr_line);
}

void	check_here_doc(char *limiter, int *fd)
{
	char	*line;
	char	*buffer;
	int		len;
	int		tmp_fd;

	buffer = NULL;
	tmp_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return;
    }
	len = ft_strlen(limiter);
	line = read_line(&buffer, STDIN_FILENO);
	if (line == NULL)
		return ;
	while (!(ft_strncmp(line, limiter, len) == 0 && line[len] == '\n'))
	{
		write(tmp_fd, line, ft_strlen(line));
		free(line);
		line = read_line(&buffer, STDIN_FILENO);
		if (line == NULL)
			return ;
	}
	free(line);
	close(tmp_fd);
	*fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}

}

int		check_redirection(t_ast *ast, t_ms **shell)
{
	int		fd;
	t_io	*ptr;
	
	(*shell)->io_in = -1;
	(*shell)->io_out = -1;
	ptr = ast->io;
	while (ptr)
	{
		ptr->value = expandcmd(ptr->value, *shell);
		if (ptr->type == T_LESS)
		{
			if ((*shell)->io_in != -1)
				close((*shell)->io_in);
			fd = open(ptr->value, O_RDONLY);
			if (fd == -1)
			{
				//ft_putstr_fd("minishell: No such file or directory\n", 2);
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
			(*shell)->io_in = fd;
		}
		else if (ptr->type == T_GREAT)
		{
			if ((*shell)->io_out != -1)
				close((*shell)->io_out);
			fd = open(ptr->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				//ft_putstr_fd("minishell: Permission denied\n", 2);
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
			(*shell)->io_out = fd;

		}
		else if (ptr->type == T_DGREAT)
		{
			if ((*shell)->io_out != -1)
				close((*shell)->io_out);
			fd = open(ptr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				//ft_putstr_fd("minishell: Permission denied\n", 2);
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
			(*shell)->io_out = fd;
		}
		else if (ptr->type == T_DLESS)
		{
			if ((*shell)->io_in != -1)
				close((*shell)->io_in);
			check_here_doc(ptr->value, &(*shell)->io_in);
		}
		ptr = ptr->next;
	}
	return (0);
}
