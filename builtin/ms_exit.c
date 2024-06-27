/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:23:59 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/27 16:14:37 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(char **arg, t_ms *shell)
{
	int		exit_value;
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
	exit_value = ft_atoi(arg[1]);
	shell->lexit_status = (256 + exit_value) % 256;
	exit_shell(shell, shell->lexit_status);
}
