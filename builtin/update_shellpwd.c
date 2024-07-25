/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shellpwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:45:40 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/25 11:22:44 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_shellpwd(t_ms *shell)
{
	int			size;
	char		*pwd;

	size = 1024;
	pwd = ft_calloc(size, sizeof(char));
	if (!pwd)
		print_error (shell, "Memory allocation failed");
	while (!getcwd(pwd, size))
	{
		free(pwd);
		size *= 2;
		pwd = ft_calloc(size, sizeof(char));
		if (!pwd)
			print_error (shell, "Memory allocation failed");
	}
	return (pwd);
}

void	update_shelloldpwd(t_ms *shell)
{
	t_envlst	*envlst;

	envlst = shell->envlst;
	while (envlst)
	{
		if (ft_strncmp(envlst->key, "PWD", 3) == 0)
		{
			shell->oldpwd = envlst->value;
			return ;
		}
		envlst = envlst->next;
	}
	shell->oldpwd = shell->pwd;
}
