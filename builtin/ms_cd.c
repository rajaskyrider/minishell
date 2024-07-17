/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:47:57 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/17 14:04:19 by tle-moel         ###   ########.fr       */
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
	if (path[2] != 0)
	{
		shell->lexit_status = 1;
		print_error(shell, "minishell: cd: too many arguments\n");
		return ;
	}
	else if (path[1] == NULL)
		cd_home(shell);
	else if (chdir(path[1]) == -1)
	{
		shell->lexit_status = 1;
		print_error(shell, "minishell: cd: No such file or directory\n");
		return ;
	}
	update_pwd(shell);
}

void	cd_home(t_ms *shell)
{
	t_envlst	*envlst;
	char		*home_dir;

	envlst = shell->environ;
	while (envlst)
	{
		if (ft_strncmp(envlst->key, "HOME", 4) == 0)
		{
			home_dir = envlst->value;
			if (chdir(home_dir) == -1)
				print_error(shell, "minishell: cd: HOME not find\n");
			return ;
		}
		envlst = envlst->next;
	}
}
