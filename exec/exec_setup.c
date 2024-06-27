/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:22:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/27 18:02:23 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		path_is_given(char *full_cmd)
{
	int	i;

	i = 0;
	while (full_cmd[i] != ' ' && full_cmd[i] != '\0')
	{
		if (full_cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**find_paths(t_envlst *environ)
{
	char	**paths;
	t_envlst *ptr;

	ptr = environ;
	while (ptr)
	{
		if (ft_strncmp(ptr->key, "PATH", 4) == 0)
			break ;
		ptr = ptr->next;
	}
	paths = ft_split(ptr->value, ':');
	return (paths);
}

char	*get_cmd(char *cmd, char **paths, t_ms *shell)
{
	int			i;
	char		*path;
	char		*path_exec;

	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		path_exec = ft_strjoin(path, cmd);
		free(path);
		if (access(path_exec, X_OK) == 0)
			return (path_exec);
		free(path_exec);
		i++;
	}
	//check_directory(cmd, shell);
	print_error(shell, "minishell: command not found\n");
	exit (127);
}
