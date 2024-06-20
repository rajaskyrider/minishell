/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:42:11 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/20 10:57:58 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo(char **arg)
{
	int	new_line;
	int	i;

	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putstr_fd("\n", 2);

	i = 1;
	new_line = 1;
	if (arg[i] && ft_strncmp(arg[i], "-n", 2) == 0)
	{
		i++;
		new_line = 0;
	}
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
