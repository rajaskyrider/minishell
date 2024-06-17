/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/17 11:25:48 by rpandipe         ###   ########.fr       */
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

char	*replace_cmd(char *cmd, char *filename, t_ms *shell)
{
	char	*newcmd;
	size_t	cmd_len;
	size_t	name_len;

	ft_putstr_fd("\n*********\n", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n*********\n", 2);
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
	ft_putstr_fd("\n*********\n", 2);
	ft_putstr_fd("replace done\n", 2);
	ft_putstr_fd("\n*********\n", 2);
	return (newcmd);
}

char	*replace_wildcard(char *cmd, char *matches, int start, t_ms *shell)
{
	int		end;
	int		clen;
	int		mlen;
	char	*newcmd;

	end = start;
	ft_putstr_fd(&cmd[start], 2);
	clen = ft_strlen(cmd);
	mlen = ft_strlen(matches);
	while (cmd[end] && cmd[end] != ' ')
		end++;
	newcmd = ft_calloc(clen + mlen - (end - start) + 1, sizeof(char));
	if (!newcmd)
		print_error(shell, "minishell: Memory Allocation Failed");
	ft_strlcpy(newcmd, cmd, start + 1);
	ft_strlcat(newcmd, matches, clen + mlen - (end - start) + 1);
	ft_strlcat(newcmd, cmd + end, clen + mlen - (end - start) + 1);
	free(cmd);
	cmd = NULL;
	return (newcmd);
}

int	glob(char **cmd, t_ms *shell, int start)
{
	struct dirent	*entry;
	DIR				*dp;
	char			*matches;
	int				end;
	char			*pattern;

	matches = NULL;
	end = start;
	while ((*cmd)[end] && (*cmd)[end] != ' ')
		end++;
	pattern = ft_substr(*cmd, start, end - start);
	ft_putstr_fd("\n*********\n", 2);
	ft_putstr_fd(pattern, 2);
	ft_putstr_fd("\n*********\n", 2);
	dp = opendir(".");
	if (!dp)
		print_error(shell, "minishell: Error opening directory");
	while ((entry = readdir(dp)))
	{
		if (match(pattern, entry->d_name))
			matches = replace_cmd(matches, entry->d_name, shell);
	}
	closedir(dp);
	free(pattern);
	ft_putstr_fd("\n*********\n", 2);
	ft_putstr_fd(matches, 2);
	ft_putstr_fd("\n*********\n", 2);
	*cmd = replace_wildcard(*cmd, matches, start, shell);
	end = start + ft_strlen(matches);
	free(matches);
	ft_putstr_fd("\n*********\n", 2);
	ft_putstr_fd(*cmd, 2);
	ft_putstr_fd("\n*********\n", 2);
	return (end);
}

char	*expandcmd(char *cmd, t_ms *shell)
{
	int		i;

	i = 0;
	ft_putstr_fd("start expand\n", 2);
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\'' \
				&& cmd[i] != '*' && cmd[i] != '$')
			i++;
		if (cmd[i] && cmd[i] == '\'')
		{
			i++;
			while (cmd[i] && cmd[i] !='\'')
				i++;	
		}
		else if (cmd[i] && cmd[i] == '\"')
		{
			i++;
			while (cmd[i] && cmd[i] !='\"')
			{
				if (cmd[i] && cmd[i] == '$')
					i = deal_dollar(&cmd, shell, i);
				i++;
			}
		}
		else if (cmd[i] && cmd[i] == '*')
			i = glob(&cmd, shell, i);
		else if (cmd[i] && cmd[i] == '$')
			i = deal_dollar(&cmd, shell, i);
		else if (cmd[i])
			i++;
	}
	ft_putstr_fd("expand done\n", 2);
	ft_putstr_fd("\n+++++++++\n", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n+++++++++\n", 2);
	return (cmd);
}
