/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:36:02 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/10 17:05:30 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void	exec_cmd(char *full_cmd, t_ms *shell)
 {
	char	**args;
	char	**paths;
	char	*tmp;

	if (is_builtin(full_cmd) == 0)
		return (exec_builtin(full_cmd));
	else if (path_is_given(full_cmd) == 0)
		return (exec_given_path(full_cmd));
	else
	{
		paths = find_path(shell->environ);
		args = ft_split(full_cmd, ' ');
		tmp = args[0];
		args[0] = get_cmd(args[0], paths, args);
		free(tmp);
		execve(args[0], args, shell->env);
	}
 }

void	exec_given_path(char *full_cmd)
{
	char	**args;
	char	**path;
	
	args = ft_split(full_cmd, ' ');
	path = args[0];
	if (access(path, X_OK) == 0)
		execve(args[0], (args + 1), NULL);
}



int		is_builtin(char *full_cmd)
{
	if (ft_strncmp(full_cmd, "echo", ft_strlen(full_cmd)) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "cd", ft_strlen(full_cmd)) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "pwd", ft_strlen(full_cmd)) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "export", ft_strlen(full_cmd)) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "unset", ft_strlen(full_cmd)) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "env", ft_strlen(full_cmd)) == 0)
		return (1);
	else if (ft_strncmp(full_cmd, "exit", ft_strlen(full_cmd)) == 0)
		return (1);
	else
		return (0);
}

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

char	*get_cmd(char *cmd, char **paths, char **args)
{
	int		i;
	char	*path;
	char	*path_exec;

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
	return (NULL);
}
