/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:09 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 16:01:53 by tle-moel         ###   ########.fr       */
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
