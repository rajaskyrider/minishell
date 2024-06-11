/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:36:02 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/11 10:42:56 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void	exec_cmd(char *full_cmd, t_ms *shell)
 {
	char	**args;
	char	**paths;
	char	*tmp;

	if (is_builtin(full_cmd, shell) == 1)
		return ;
	else if (path_is_given(full_cmd) == 1)
		return (exec_given_path(full_cmd));
	else
	{
		paths = find_paths(shell->environ);
		args = ft_split(full_cmd, ' ');
		tmp = args[0];
		args[0] = get_cmd(args[0], paths);
		free(tmp);
		execve(args[0], args, shell->env);
	}
 }

void	exec_given_path(char *full_cmd)
{
	char	**args;
	char	*path;
	
	args = ft_split(full_cmd, ' ');
	path = args[0];
	if (path )
	if (access(path, X_OK) == 0)
		execve(args[0], (args + 1), NULL);
}

int		is_builtin(char *full_cmd, t_ms *shell)
{
	char	**arg;

	arg = ft_split(full_cmd, ' ');
	if (ft_strncmp(full_cmd, "echo ", 5) == 0)
		return (ms_echo(arg), 1);
	else if (ft_strncmp(full_cmd, "cd ", 3) == 0)
		return (ms_cd(shell, arg), 1);
	else if (ft_strncmp(full_cmd, "pwd ", 4) == 0)
		return (ms_pwd(shell), 1);
	else if (ft_strncmp(full_cmd, "export ", 7) == 0)
		return (ms_export(arg, shell), 1);
	else if (ft_strncmp(full_cmd, "unset ", 6) == 0)
		return (ms_unset(arg, shell), 1);
	else if (ft_strncmp(full_cmd, "env ", 4) == 0)
		return (ms_env(shell), 1);
	else if (ft_strncmp(full_cmd, "exit ", 5) == 0)
		return (exit_shell(shell, EXIT_SUCCESS), 1);
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

char	*get_cmd(char *cmd, char **paths)
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
