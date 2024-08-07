/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:31:19 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/05 11:35:14 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_ms *shell)
{
	t_envlst	*envlst;

	envlst = shell->envlst;
	while (envlst && ft_strncmp(envlst->key, "PWD", 4) != 0)
		envlst = envlst->next;
	if (envlst)
		ft_printf("%s\n", envlst->value);
	else
		ft_printf("%s\n", get_shellpwd(shell));
	shell->lexit_status = 0;
}
