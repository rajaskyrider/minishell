/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:31:19 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 10:18:19 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_ms *shell)
{
	t_envlst	*envlst;

	envlst = shell->environ;
	while (envlst && ft_strncmp(envlst->key, "pwd", 3) == 0)
		envlst = envlst->next;
	if (envlst)
		ft_printf("%s\n", envlst->value);
	else
		print_error(shell, "Internal Error");
}
