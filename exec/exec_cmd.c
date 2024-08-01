/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:51:01 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/01 15:02:17 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *full_cmd, t_ms *shell, char **arg)
{
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
	else if (ms_strcmp(arg[0], "exit") == 0)
		return (ms_exit(arg, shell), 1);
	else
		return (0);
}

void	exec_given_path(char *full_cmd, t_ms *shell, char **args)
{
	char	*path;
	char	*cwd;
	char	*tmp;
	int		i;

	i = 0;
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
	check_directory(full_cmd, shell);
	if (access(path, X_OK) == 0)
		execve(args[0], args, shell->env);
	else
	{
		print_error(shell, "minishell: Permission denied\n");
		exit (126);
	}
}

void	run_cmd(t_ms *shell, char **arg)
{
	char	**paths;
	char	*tmp;

	if (path_is_given(arg[0]) == 1)
		return (exec_given_path(arg[0], shell, arg));
	else
	{
		paths = find_paths(shell->envlst);
		if (!paths)
		{
			shell->lexit_status = 127;
			ft_putstr_fd("minishell: no such file or directory\n", 2);
			exit(127);
		}
		tmp = arg[0];
		arg[0] = get_cmd(arg[0], paths, shell);
		free(tmp);
		execve(arg[0], arg, shell->env);
	}
}

void	exec_not_piped(t_ms *shell, char **args)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		close_fd(shell);
		if (ft_strlen(args[0]) == 0)
			exit_shell(shell, 0);
		run_cmd(shell, args);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->lexit_status = WEXITSTATUS(status);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	exec_cmd(t_ast *ast, char *full_cmd, t_ms *shell, int piped)
{
	char	**args;

	signal_process();
	args = split_and_expand(full_cmd, shell);
	if (deal_redirection(ast, shell) != 0)
	{
		if (piped != 0)
			exit(EXIT_FAILURE);
		shell->lexit_status = 1;
		return ;
	}
	if (is_builtin(full_cmd, shell, args) == 1)
	{
		if (piped != 0)
			exit(EXIT_SUCCESS);
	}
	else if (piped == 0)
		exec_not_piped(shell, args);
	else
		run_cmd(shell, args);
	free_args(args);
}
