/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:40 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 11:07:00 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Initialitize the struct, edit when new members are added
/// @param shell The struct to initialize
void	init_shell(t_ms *shell, char **env)
{
	shell->cmd = NULL;
	shell->ast = NULL;
	shell->token_lst = NULL;
	shell->environ = init_environ(env);
	shell->env = env;
	shell->error = 0;
}

/// @brief Exit the shell by freeing all allocated memory, 
///        edit when new members are added
/// @param shell The main struct
/// @param exitcode EXIT_SUCCESS or EXIT_FAILURE
void	exit_shell(t_ms *shell, int exitcode)
{
	clear_shell(shell);
	exit(exitcode);
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
		cmd = readline("\x1b[35mminishell>\x1b[0m ");
		if (cmd)
			readprompt(&shell, cmd);
	}
}
