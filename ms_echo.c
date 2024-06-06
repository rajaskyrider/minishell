/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:42:11 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/06 14:58:02 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ms_echo(char **arg)
{
    int     new_line;
    int     i;

    i = 1;
    new_line = 1;
    if (ft_strncmp(arg[i], "-n", 2) == 0)
    {
        i++;
        new_line = 0;
    }
    while (arg[i] != NULL)
    {
        ft_putstr_fd(arg[i], 1);
        if (arg[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (new_line == 1)
        ft_putstr_fd("\n", 1);
}
