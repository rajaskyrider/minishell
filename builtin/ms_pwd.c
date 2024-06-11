/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:31:19 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 09:36:38 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_pwd(t_ms *shell)
{
	t_envlst	*envlst;

	envlst = shell->environ;
	while (envlst && ft_strncmp(envlst->key, "PWD", 3) == 0)
		envlst = envlst->next;
	if (envlst)
		return (envlst->value);
	else
		print_error(shell, "Internal Error");
	return (NULL);
}
