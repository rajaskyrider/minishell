/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:40:18 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/18 10:36:24 by rpandipe         ###   ########.fr       */
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

	result = NULL;
	end = start;
	while ((*cmd)[end] && (*cmd)[end] != ' ')
		end++;
	if (end - start == 1)
		return (end);
	pattern = ft_substr(*cmd, start + 1, end - start + 1);
	env_val = ms_getenv(pattern, shell);
	if (env_val)
		result = ft_strdup(env_val);
	else
		result = ft_strdup("");
	free(pattern);
	*cmd = replace_wildcard(*cmd, result, start, shell);
	end = start + ft_strlen(result);
	free(result);
	return (end);
}


int find_start(char *cmd, int start)
{
	while (start > 0  && cmd[start] != ' ')
		start--;
	return (start + 1);
}
