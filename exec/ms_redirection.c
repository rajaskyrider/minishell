/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:40:20 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/27 15:08:28 by rpandipe         ###   ########.fr       */
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
				print_error(*shell, "minishell: No such file or directory\n");
				(*shell)->lexit_status = 1;
				exit(1);
			}
			else
				(*shell)->io_in = fd;
		}
		else if (ptr->type == T_GREAT)
		{
			fd = open(ptr->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				exit(EXIT_FAILURE);
				//print_error(*shell,  "minishell: Permission denied");	
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
