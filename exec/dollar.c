/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:40:18 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/18 12:00:45 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv(char *key, t_ms *shell)
{
	t_envlst	*elst;

	elst = shell->environ;
	while (elst)
	{
		if (ft_strncmp(key, elst->key, ft_strlen(key) + 1) == 0)
			return (elst->value);
		elst = elst->next;
	}
	return (NULL);
}

int	replace_invalid(char **cmd, int start, int end, t_ms *shell)
{
	char	*newcmd;
	int		len;

	len = ft_strlen(*cmd) - (end - start);
	newcmd = ft_calloc(len + 1, sizeof(char));
	if (!newcmd)
		print_error(shell, "minishell: Memory Allocation Failed");
	ft_strlcpy(newcmd, *cmd, start + 1);
	ft_strlcat(newcmd, *cmd + end, len + 1);
	free (*cmd);
	printf("%s\n",  newcmd);
	printf("%d\n",  start);
	*cmd = newcmd;
	return (start - 2);
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
	free(pattern);
	if (result)
	{
		*cmd = replace_wildcard(*cmd, result, start, shell);
		end = start + ft_strlen(result);
		free(result);
	}
	else
		end = replace_invalid(cmd, start, end, shell);
	ft_putstr_fd("out out", 2);
	return (end);
}


int find_start(char *cmd, int start)
{
	while (start > 0  && cmd[start] != ' ')
		start--;
	return (start + 1);
}
