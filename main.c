/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:40 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/23 09:31:34 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Initialitize the struct, edit when new members are added
/// @param shell The struct to initialize
void	init_shell(t_ms *shell)
{
	shell->cmd = NULL;
}

/// @brief Exit the shell by freeing all allocated memory, 
///        edit when new members are added
/// @param shell The main struct
/// @param exitcode EXIT_SUCCESS or EXIT_FAILURE
void	exit_shell(t_ms *shell, int exitcode)
{
	if (shell->cmd)
		free(shell->cmd);
	exit(exitcode);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	shell;
	char	*cmd;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	while (1)
	{
		cmd = readline("\x1b[35mminishell>\x1b[0m ");
		if (cmd)
			readprompt(&shell, cmd);
		//print_token_lst(shell);
	}
}
