/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/13 11:34:07 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match(char *pattern, char *filename)
{
	if (*pattern == 0)
		return (*filename == 0);
	if (*pattern == '*')
		return (match(pattern + 1, filename) || \
				(*filename && match(pattern, filename + 1)));
	if (*pattern == *filename)
		return (match(pattern + 1, filename + 1));
	return (0);	
}

void	replace_cmd(char *cmd, char *filename, t_ms *shell)
{
	char	*newcmd;
	size_t	cmd_len;
	size_t	name_len;

	cmd_len = ft_strlen(cmd);
	name_len = ft_strlen(filename);
	newcmd = ft_calloc(cmd_len + name_len + 2, sizeof(char));
	if (!newcmd)
		print_error(shell, "minishell: Memory Allocation Failed");
	ft_strlcpy(newcmd, cmd, cmd_len + 1);
	ft_strlcat(newcmd, " ", cmd_len + name_len + 2);
	ft_strlcat(newcmd, filename, cmd_len + name_len + 2);
	if (cmd)
		free(cmd);
	cmd = newcmd;
}

char	*glob(char *pattern, t_ms *shell)
{
	struct dirent	*entry;
	DIR				*dp;
	char			*matches;

	matches = NULL;
	dp = opendir(".");
	if (!dp)
		print_error(shell, "minishell: Error opening directory");
	while ((entry = readdir(dp)))
	{
		if (match(pattern, entry->d_name))
			replace_cmd(matches, entry->d_name, shell);
	}
	return (matches);
}
