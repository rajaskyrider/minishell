/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:11:48 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/06 16:46:30 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	deal_redirection(t_ast *ast, t_ms *shell)
{
	int	res;

	res = 0;
	if (ast)
		res = check_redirection(ast, &shell);
	if (shell->io_in != -1)
		dup2(shell->io_in, STDIN_FILENO);
	if (shell->io_out != -1)
		dup2(shell->io_out, STDOUT_FILENO);
	close_fd(shell);
	return (res);
}

char	**split_again(char **arg, int size)
{
	char	*exp_arg;
	int		i;

	i = 1;
	exp_arg = NULL;
	exp_arg = ft_calloc(size + 1, sizeof(char));
	ft_strlcpy(exp_arg, arg[0], ft_strlen(arg[0]) + 1);
	free(arg[0]);
	ft_strlcat(exp_arg, " ", size + 1);
	while (arg[i])
	{
		ft_strlcat(exp_arg, arg[i], size + 1);
		ft_strlcat(exp_arg, " ", size + 1);
		free(arg[i]);
		i++;
	}
	free(arg);
	arg = ms_split(exp_arg, ' ');
	free(exp_arg);
	return (arg);
}

char	**split_and_expand(char *full_cmd, t_ms *shell)
{
	char	**arg;
	int		i;
	int		size;
	int		exp_size;
	int		flag;

	i = 0;
	size = 0;
	exp_size = 0;
	flag = 0;
	arg = ms_split(full_cmd, ' ');
	if ((ms_strcmp(arg[0], "echo") == 0 && arg[1] && arg[1][0] == '"'))
		flag = 1;
	while (arg[i])
	{
		size += ft_strlen(arg[i]) + 1;
		arg[i] = expandcmd(arg[i], shell);
		exp_size += ft_strlen(arg[i]) + 1;
		i++;
	}
	if (exp_size > size && flag == 0)
		arg = split_again(arg, exp_size);
	if (arg[0][0] == 0 && arg[1])
		arg = split_again(arg, exp_size);
	return (arg);
}

void	check_directory(char *cmd, t_ms *shell)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit_process(shell, 126);
	}
	else if (stat(cmd, &statbuf) != 0)
	{
		print_error(shell, "minishell: No such file or directory\n");
		exit_process(shell, 127);
	}
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
