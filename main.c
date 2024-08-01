/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:45:40 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/01 16:43:47 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_ms *shell, char **env)
{
	shell->cmd = NULL;
	shell->ast = NULL;
	shell->token_lst = NULL;
	shell->env = init_env(env);
	shell->envlst = init_envlst(env);
	shell->pwd = NULL;
	shell->oldpwd = NULL;
	shell->error = 0;
	shell->io_in = -1;
	shell->io_out = -1;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->lexit_status = 0;
}

void	exit_shell(t_ms *shell, int exitcode)
{
	clean_shell(shell);
	//clear_shell(shell);
	exit(exitcode);
}

void	clean_shell(t_ms *shell)
{
	if (shell->std_in !=-1)
		close(shell->std_in);
	if (shell->std_out != -1)
		close(shell->std_out);
	clean_env(shell->env);
	delete_env_lst(&(shell->envlst));
	clear_shell(shell);
}

int	handle_paste(int count, int key)
{
	(void)count;
	(void)key;
	rl_redisplay();
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	shell;
	char	*cmd;

	(void)argc;
	(void)argv;
	rl_bind_keyseq("\\e[200~", handle_paste);
    rl_bind_keyseq("\\e[201~", (rl_command_func_t *)rl_redisplay);
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
