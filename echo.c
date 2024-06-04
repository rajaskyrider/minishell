/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:44:48 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/04 10:57:22 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_newline(char	**str)
{
	char	*check;

	check = *str;
	while ( check && *check == ' ')
	{
		
	}
}

int	ft_echo(char *str)
{
	int	opt;

	opt = check_n(&str);
}