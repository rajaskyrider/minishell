/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:48:26 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 15:26:34 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_export(char **arg, t_ms *shell)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (arg[i] == NULL)
		return (print_export(shell->environ));
	while (arg[i] != NULL)
	{
		key = extract_key(arg[i]);
		if (key_is_valid(key) == 0)
		{
			free(key);
			shell->lexit_status = 1;
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		}
		else
		{
			value = extract_value(arg[i]);
			if (key)
				update_envlst(key, value, &shell->environ);
		}
		i++;
	}
	shell->env = update_env(shell);
}

int		key_is_valid(char *key)
{
	int		i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
	 	return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(t_envlst *environ)
{
	t_envlst	*ptr;
	t_envlst	*ptr2;
	char		*curr_key;

	curr_key = find_min_key(environ);
	ptr = environ;
	while (ptr)
	{
		ptr2 = environ;
		while (curr_key && ft_strncmp(curr_key, ptr2->key, \
				ft_strlen(curr_key)) != 0 && ptr2)
			ptr2 = ptr2->next;
		if (curr_key && ft_strncmp(ptr2->key, "_", 2) != 0)
		{
			ft_putstr_fd("declar -x ", 1);
			ft_putstr_fd(ptr2->key, 1);
			if (ptr2->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(ptr2->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		if (ptr->next)
			curr_key = find_next_key(curr_key, environ);
		ptr = ptr->next;
	}
}

char	*find_min_key(t_envlst *environ)
{
	t_envlst	*ptr;
	char		*min;

	ptr = environ;
	min = ptr->key;
	while (ptr)
	{
		if (ft_strncmp(ptr->key, min, ft_strlen(ptr->key)) < 0)
			min = ptr->key;
		ptr = ptr->next;
	}
	return (min);
}

char	*find_next_key(char *curr_key, t_envlst *environ)
{
	t_envlst	*ptr;
	char		*next_key;
	int			cmp;

	next_key = NULL;
	ptr = environ;
	while (ptr)
	{
		cmp = ft_strncmp(ptr->key, curr_key, ft_strlen(ptr->key));
		if (cmp > 0)
		{
			if (next_key == NULL || \
				ft_strncmp(ptr->key, next_key, ft_strlen(ptr->key)) < 0)
				next_key = ptr->key;
		}
		ptr = ptr->next;
	}
	return (next_key);
}
