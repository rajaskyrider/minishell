/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:42:11 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/18 17:59:10 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo(char **arg)
{
	int	new_line;
	int	i;

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
