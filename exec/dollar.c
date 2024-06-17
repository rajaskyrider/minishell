/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:40:18 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/17 11:40:27 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv(char *key, t_ms *shell)
{
	t_envlst	*elst;

	elst = shell->environ;
	while (elst)
	{
		if (ft_strncmp(key, elst->key, ft_strlen(elst->key)) == 0)
			return (elst->value);
		elst = elst->next;
	}
	return (" ");
}

int	deal_dollar(char **cmd, t_ms *shell, int start)
{
	char		*result;
	const char	*env_val;
	char		*pattern;
	int			end;

	ft_putstr_fd("start dollar\n", 2);
	result = NULL;
	end = start;
	ft_putstr_fd("start.....\n", 2);
	while ((*cmd)[end] && (*cmd)[end] != ' ')
		end++;
	ft_putstr_fd("here\n", 2);
	if (end - start == 1)
		return (end);
	pattern = ft_substr(*cmd, start + 1, end - start + 1);
	env_val = ms_getenv(pattern, shell);
	ft_putstr_fd("here 2\n", 2);
	if (env_val)
		result = ft_strdup(env_val);
	else
		result = ft_strdup("");
	free(pattern);
	ft_putstr_fd("\n--RESULT-------\n", 2);
	ft_putstr_fd(result, 2);
	ft_putstr_fd("\n---------\n", 2);
	ft_putstr_fd("start wc expand\n", 2);
	*cmd = replace_wildcard(*cmd, result, start, shell);
	ft_putstr_fd(result, 2);
	ft_putstr_fd("\n---------\n", 2);
	ft_putstr_fd(*cmd, 2);
	ft_putstr_fd("\n---------\n", 2);
	end = start + ft_strlen(result);
	free(result);
	ft_putstr_fd("end dollar\n", 2);
	return (end);
}
