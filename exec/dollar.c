/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:40:18 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/17 13:02:52 by tle-moel         ###   ########.fr       */
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
	*cmd = newcmd;
	return (start - 2);
}

int	check_question(char **cmd, t_ms *shell, int start)
{
	char	*result;

	if ((*cmd)[start] != '?')
		return (0);
	result = ft_itoa(shell->lexit_status);
	*cmd = replace_wildcard(*cmd, result, start - 1, shell);
	free (result);
	return (1);
}

int	deal_dollar(char **cmd, t_ms *shell, int start)
{
	char		*result;
	const char	*env_val;
	char		*pattern;
	int			end;

	if (check_question(cmd, shell, start))
		return (start);
	result = NULL;
	end = start;
	while ((*cmd)[end] && (*cmd)[end] != ' ' \
			&& (*cmd)[end] != '$' && (*cmd)[end] != '\"')
		end++;
	if (start == end)
		return (end - 1);
	pattern = ft_substr(*cmd, start, end - start);
	env_val = ms_getenv(pattern, shell);
	if (env_val)
		result = ft_strdup(env_val);
	free(pattern);
	if (result)
	{
		*cmd = replace_wildcard(*cmd, result, start - 1, shell);
		end = start + ft_strlen(result);
		free(result);
	}
	else
		end = replace_invalid(cmd, start - 1, end, shell);
	return (end - 1);
}
int find_start(char *cmd, int start)
{
	while (start > 0  && cmd[start] != ' ')
		start--;
	return (start + 1);
}

void	remove_quotes(char **cmd, int start, int end)
{
	int		len;
	char	*newcmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(*cmd);
	newcmd = ft_calloc(len - 1, sizeof(char));
	while ((*cmd)[i])
	{
		if (i != start && i != end)
			newcmd[j++] = (*cmd)[i];
		i++;
	}
	free(*cmd);
	*cmd = newcmd;
}
