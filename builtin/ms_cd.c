/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:47:57 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/11 10:23:10 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_ms *shell)
{
	char	*pwd;
	int		size;

	size = 1024;
	pwd = ft_calloc(size, sizeof(char));
	if (!pwd)
		print_error (shell, "Memory allocation failed");
	while (!getcwd(pwd, sizeof(pwd)))
	{
		free(pwd);
		size *= 2;
		pwd = ft_calloc(size, sizeof(char));
		if (!pwd)
			print_error (shell, "Memory allocation failed");
	}
	return (pwd);
}

void	update_pwd(t_ms *shell)
{
	char		*pwd;
	t_envlst	*oldpwd_node;
	t_envlst	*pwd_node;
	t_envlst	*envlst;

	oldpwd_node = NULL;
	pwd_node = NULL;
	envlst = shell->environ;
	pwd = get_path(shell);
	while (envlst && (!oldpwd_node || !pwd_node))
	{
		if (ft_strncmp(envlst->key, "PWD", 3) == 0)
			pwd_node = envlst;
		else if (ft_strncmp(envlst->key, "OLDPWD", 6) == 0)
			oldpwd_node = envlst;
		envlst = envlst->next;
	}
	free(oldpwd_node->value);
	oldpwd_node->value = pwd_node->value;
	pwd_node->value = ft_strdup(pwd);
	free(pwd);
}

void	ms_cd(t_ms *shell, char **path)
{
	if (chdir(path[1]) == -1)
		print_error(shell, "minishell: cd: No such file or directory");
	else
	{
		update_pwd(shell);
	}
}
