/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:04:28 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/06 15:41:24 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readprompt(t_ms *shell, char *new_cmd)
{
	if (!shell->cmd || ft_strncmp(new_cmd, shell->cmd, ft_strlen(new_cmd)) != 0)
		add_history(new_cmd);
	if (shell->cmd)
		free(shell->cmd);
	shell->cmd = new_cmd;
	if (new_cmd[0] == '\0')
		return ;
	if (ft_strncmp(shell->cmd, "exit", ft_strlen(shell->cmd)) == 0)
		exit_shell(shell, EXIT_SUCCESS);
	if (tokenize(shell) == 0)
		return ;
	if (parser(shell) == 0)
		return ;
	execute(shell);
	clear_shell(shell);
}
