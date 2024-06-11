/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:31:19 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 11:52:43 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_ms *shell)
{
	t_envlst	*envlst;

	envlst = shell->environ;
	while (envlst && ft_strncmp(envlst->key, "PWD", 3) == 0)
		envlst = envlst->next;
	if (envlst)
		ft_printf("%s\n", envlst->value);
	else
		print_error(shell, "Internal Error");
}
