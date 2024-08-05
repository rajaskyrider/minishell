/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:42:11 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/05 11:34:26 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo(t_ms *shell, char **arg)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	while (arg[i] && ms_strcmp(arg[i], "-n") == 0)
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
	shell->lexit_status = 0;
}
