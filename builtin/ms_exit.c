/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:23:59 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 13:25:32 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(char **arg, t_ms *shell)
{
	long long	exit_value;
	int		i;

	i = 0;

	if (arg[1] == NULL)
		exit_shell(shell, EXIT_SUCCESS);
	if (arg[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->lexit_status = 1;
		return ;
	}
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]) && arg[1][i] != '+' && arg[1][i] != '-')
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit_shell(shell, 2);
		}
		i++;
	}
	exit_value = ft_atoll(arg[1]);
	if (exit_value < 0)
		shell->lexit_status = (exit_value + 256) % 256;
	else
		shell->lexit_status = (exit_value - 256) % 256;
	exit_shell(shell, shell->lexit_status);
}
