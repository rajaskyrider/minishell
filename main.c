/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:40 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/23 14:04:32 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_ms *shell, char **env)
{
	shell->cmd = NULL;
	shell->ast = NULL;
	shell->token_lst = NULL;
	shell->environ = init_environ(env);
	shell->env = init_env(env);
	shell->error = 0;
	//shell->pip[0] = dup(STDIN_FILENO);
	//shell->pip[1] = dup(STDOUT_FILENO);
	shell->io_in = -1;
	shell->io_out = -1;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->lexit_status = 0;
}

void	exit_shell(t_ms *shell, int exitcode)
{
	clean_shell(shell);
	clear_shell(shell);
	exit(exitcode);
}

void	clean_shell(t_ms *shell)
{
	close(shell->std_in);
	close(shell->std_out);
	clean_env(shell->env);
	delete_env_lst(&(shell->environ));
	clear_shell(shell);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	shell;
	char	*cmd;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		init_signal();
		cmd = readline("\x1b[35mminishell>\x1b[0m ");
		if (!cmd)
		{
			clean_shell(&shell);
			printf("exit\n");
			break ;
		}
		if (cmd)
			readprompt(&shell, cmd);
	}
	return (0);
}
