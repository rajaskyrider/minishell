/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:55:29 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/10 11:12:58 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(char **arg, t_ms *shell)
{
	int		i;

	i = 1;
	while (arg[i] != NULL)
	{
		delete_env_node(shell->environ);
	}
}

void	delete_env_node(t_envlst *environ)
{
	(void)environ;
	return ;
}