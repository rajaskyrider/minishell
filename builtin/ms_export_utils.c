/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:09 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/26 10:42:21 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_is_valid(char *key)
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

char	*find_min_key(t_envlst *environ)
{
	t_envlst	*ptr;
	char		*min;

	ptr = environ;
	min = ptr->key;
	while (ptr)
	{
		if (ms_strcmp(ptr->key, min) < 0)
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
		cmp = ms_strcmp(ptr->key, curr_key);
		if (cmp > 0)
		{
			if (next_key == NULL || \
				ms_strcmp(ptr->key, next_key) < 0)
				next_key = ptr->key;
		}
		ptr = ptr->next;
	}
	return (next_key);
}
