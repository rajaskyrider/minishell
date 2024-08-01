/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:22:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/01 15:24:04 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_is_given(char *full_cmd)
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
	char		**paths;
	t_envlst	*ptr;

	paths = NULL;
	ptr = environ;
	while (ptr)
	{
		if (ft_strncmp(ptr->key, "PATH", 4) == 0)
			break ;
		ptr = ptr->next;
	}
	if (ptr)
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
	print_error(shell, "minishell: command not found\n");
	clear_shell(shell);
	exit(127);
}
