/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:36:02 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/20 11:03:07 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void	exec_cmd(char *full_cmd, t_ms *shell, int piped)
{
	char	**args;
	char	**paths;
	char	*tmp;
	int		pid;
	int		status;
	int		i;

	ft_putstr_fd("exec cmd\n", 2);
	i = 0;
	if (is_builtin(full_cmd, shell, piped) == 1)
	{
		if (piped == 0)
			return ;
		else
			exit(EXIT_SUCCESS);
	}
	if (piped == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			check_redirection(shell->ast, &shell);
			if (shell->io_in != -1)
				dup2(shell->io_in, STDIN_FILENO);
			if (shell->io_out != -1)
				dup2(shell->io_out, STDOUT_FILENO);
			if (path_is_given(full_cmd) == 1)
				return (exec_given_path(full_cmd, shell));
			else
			{
				paths = find_paths(shell->environ);
				args = ms_split(full_cmd, ' ');
				while (args[i])
				{
					args[i] = expandcmd(args[i], shell);
					i++;
				}
				tmp = args[0];
				args[0] = get_cmd(args[0], paths);
				free(tmp);
				execve(args[0], args, shell->env);
			}
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->lexit_status = WEXITSTATUS(status);
	}
	else
	{
		if (path_is_given(full_cmd) == 1)
			return (exec_given_path(full_cmd, shell));
		else
		{
			paths = find_paths(shell->environ);
			args = ms_split(full_cmd, ' ');
			while (args[i])
			{
				args[i] = expandcmd(args[i], shell);
				i++;
			}
			tmp = args[0];
			args[0] = get_cmd(args[0], paths);
			free(tmp);
			execve(args[0], args, shell->env);
		}
	}
}

void	exec_given_path(char *full_cmd, t_ms *shell)
{
	char	**args;
	char	*path;
	char	*cwd;
	char	*tmp;
	int		i;

	i = 0;
	args = ms_split(full_cmd, ' ');
	while (args[i])
	{
		args[i] = expandcmd(args[i], shell);
		i++;
	}
	path = args[0];
	if (path[0] != '.' && path[0] != '/')
	{
		tmp = get_path(shell);
		cwd = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(cwd, "/");
		free(cwd);
		path = ft_strjoin(tmp, path);
		free(tmp);
	}
	if (access(path, X_OK) == 0)
		execve(args[0], args, NULL);
}

int		is_builtin(char *full_cmd, t_ms *shell, int piped)
{
	char	**arg;
	int		i;

	
	if (piped == 0)
	{
		check_redirection(shell->ast, &shell);
		ft_putstr_fd("HERE\n", 2);
		if (shell->io_in != -1)
			dup2(shell->io_in, STDIN_FILENO);
		if (shell->io_out != -1)
			dup2(shell->io_out, STDOUT_FILENO);
	}
	i = 0;
	
	arg = ms_split(full_cmd, ' ');
	while (arg[i])
	{
		arg[i] = expandcmd(arg[i], shell);
		i++;
	}
	if (ms_strcmp(full_cmd, "echo") == 0)
		return (ms_echo(arg), 1);
	else if (ms_strcmp(full_cmd, "cd") == 0)
		return (ms_cd(shell, arg), 1);
	else if (ms_strcmp(full_cmd, "pwd") == 0)
		return (ms_pwd(shell), 1);
	else if (ms_strcmp(full_cmd, "export") == 0)
		return (ms_export(arg, shell), 1);
	else if (ms_strcmp(full_cmd, "export") == 0)
		return (ms_export(arg, shell), 1);
	else if (ms_strcmp(full_cmd, "unset") == 0)
		return (ms_unset(arg, shell), 1);
	else if (ms_strcmp(full_cmd, "env") == 0)
		return (ms_env(shell), 1);
	else if (ms_strcmp(full_cmd, "exit") == 0)
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
