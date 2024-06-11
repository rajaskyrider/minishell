/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:04:28 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 10:45:06 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Adds the command line to the t_ms struct and history(if needed)
/// @param shell The main struct in t_ms
/// @param new_cmd The user input from the command line
void	readprompt(t_ms *shell, char *new_cmd)
{
	if (!shell->cmd || ft_strncmp(new_cmd, shell->cmd, ft_strlen(new_cmd)) != 0)
		add_history(new_cmd);
	if (shell->cmd)
		free(shell->cmd);
	shell->cmd = new_cmd;
	if (ft_strncmp(shell->cmd, "exit", ft_strlen(shell->cmd)) == 0)
		exit_shell(shell, EXIT_SUCCESS);
	tokenize(shell);
	//print_token_lst(shell);
	parser(shell);
	exec_cmd(shell->ast->value, shell);
}
