/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:48:26 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 16:01:44 by tle-moel         ###   ########.fr       */
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
		return (print_export(shell->envlst));
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
				update_envlst(key, value, &shell->envlst);
		}
		i++;
	}
	shell->env = update_env(shell);
}

void	print_value(char *value)
{
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(value, 1);
	ft_putstr_fd("\"", 1);
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
				print_value(ptr2->value);
			ft_putstr_fd("\n", 1);
		}
		if (ptr->next)
			curr_key = find_next_key(curr_key, environ);
		ptr = ptr->next;
	}
}
