/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:51:39 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/06 15:41:39 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_process(void)
{
	signal(SIGINT, handle_sigint_process);
	signal(SIGQUIT, handle_sigquit_process);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_process(int sig)
{
	(void)sig;
	printf("\n");
}

void	handle_sigquit_process(int sig)
{
	(void) sig;
	printf("Quit: %d\n", sig);
}
