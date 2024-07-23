/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:29:28 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 15:30:44 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(char **env)
{
	int		size;
	int		i;
	char	**my_env;

	size = 0;
	while (env[size])
		size++;
	my_env = calloc(size + 1, sizeof(char *));
	if (my_env == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

void	clean_env(char	**env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	count_env_elements(t_envlst *environ)
{
	int			count;
	t_envlst	*ptr;

	count = 0;
	ptr = environ;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

char	**update_env(t_ms *shell)
{
	int			size;
	int			i;
	char		*tmp;
	char		**new_env;
	t_envlst	*ptr;

	clean_env(shell->env);
	size = count_env_elements(shell->environ);
	new_env = calloc(size + 1, sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	ptr = shell->environ;
	i = 0;
	while (ptr)
	{
		tmp = ft_strjoin(ptr->key, "=");
		new_env[i] = ft_strjoin(tmp, ptr->value);
		free(tmp);
		i++;
		ptr = ptr->next;
	}
	new_env[i] = NULL;
	return (new_env);
}