/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:23:59 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/05 13:17:09 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	round_exit_value(long long exit_value, t_ms *shell)
{
	if (exit_value < 0)
		shell->lexit_status = (exit_value + 256) % 256;
	else
		shell->lexit_status = (exit_value - 256) % 256;
}

int	checkoverflow(char *str)
{
	int	digits;
	int	count;

	count = 0;
	if (*str == '-')
		count = 1;
	digits = ft_strlen(str + count);
	if (digits > 19)
		return (1);
	if (digits == 19)
	{
		if (count == 0)
		{
			if (!(ft_strncmp(str, "9223372036854775807", digits) <= 0))
				return (1);
		}
		else
		{
			if (!(ft_strncmp(str, "-9223372036854775808", 20) <= 0))
				return (1);
		}
	}
	return (0);
}

void	exit_error(t_ms *shell)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	exit_shell(shell, 2);
}

void	ms_exit(char **arg, t_ms *shell)
{
	long long	exit_value;
	int			i;

	i = 1;
	if (arg[1] == NULL)
		exit_shell(shell, EXIT_SUCCESS);
	if (checkoverflow(arg[1]))
		exit_error(shell);
	if (!ft_isdigit(arg[1][0]) && arg[1][0] != '+' && arg[1][0] != '-')
		exit_error(shell);
	if (arg[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->lexit_status = 1;
		return ;
	}
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]))
			exit_error(shell);
		i++;
	}
	exit_value = ft_atoll(arg[1]);
	round_exit_value(exit_value, shell);
	exit_shell(shell, shell->lexit_status);
}
