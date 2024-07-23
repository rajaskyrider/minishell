/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:36:02 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 15:53:40 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *env_line)
{
	int	i;

	i = 0;
	if (env_line == NULL)
		return (NULL);
	while (env_line[i] != '\0')
	{
		if (env_line[i] == '=')
			return (ft_substr(env_line, 0, i));
		i++;
	}
	return (env_line);
}

char	*extract_value(char *env_line)
{
	int	i;

	i = 0;
	if (env_line == NULL)
		return (NULL);
	while (env_line[i] != '\0')
	{
		if (env_line[i] == '=')
			return (ft_substr(env_line, i + 1, ft_strlen(env_line) - i - 1));
		i++;
	}
	return (NULL);
}
