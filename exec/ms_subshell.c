/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:57:22 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/25 14:38:46 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_subshell(t_ast *ast, t_ms *shell)
{
	t_ms	subshell;
	int		pid;
	int		status;

	dprintf(2, "inside subshell\n");
	pid = fork();
	if (pid == 0)
	{
		init_shell(&subshell, shell->env);
		readprompt(&subshell, ast->value);
		exit(subshell.lexit_status);
	}
	wait(&status);
	if (WIFEXITED(status))
		shell->lexit_status = WEXITSTATUS(status);
}