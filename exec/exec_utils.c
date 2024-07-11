/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:11:48 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/11 12:13:12 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		deal_redirection(t_ast *ast, t_ms *shell)
{
	int		res;

	res = 0;
	if (ast)
		res = check_redirection(ast, &shell);
	if (shell->io_in != -1)
		dup2(shell->io_in, STDIN_FILENO);
	if (shell->io_out != -1)
		dup2(shell->io_out, STDOUT_FILENO);
	return (res);
}

char	**split_and_expand(char *full_cmd, t_ms *shell)
{
	char	**arg;
	int		i;
	
	i = 0;
	arg = ms_split(full_cmd, ' ');
	while (arg[i])
	{
		arg[i] = expandcmd(arg[i], shell);
		i++;
	}
	if (arg[0][0] == 0 && arg[1])
		arg++;
	return (arg);
}

void	check_directory(char *cmd, t_ms *shell)
{
	struct stat	statbuf;
	
	if (stat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		print_error(shell, "minishell: Is a directory\n");
		exit (126);
	}
	else if (stat(cmd, &statbuf) != 0)
	{
		print_error(shell, "minishell: No such file or directory\n");
		exit (127);
	}
}

void	close_fd(t_ms *shell)
{
	if (shell->io_in != -1)
	{
		close(shell->io_in);
		shell->io_in = -1;
	}
	if (shell->io_out != -1)
	{
		close(shell->io_out);
		shell->io_out = -1;
	}
}
