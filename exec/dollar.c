/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:40:18 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/17 10:07:22 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	deal_dollar(char **cmd, t_ms *shell, int start)
{
	char		*result;
	const char	*env_val;
	char		*pattern;
	int			end;

	result = NULL;
	end = start;
	while (*cmd[end] != ' ')
		end++;
	if (end - start == 1)
		return (end);
	pattern = ft_substr(*cmd, start, end - start);
	env_val = getenv(pattern);
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
