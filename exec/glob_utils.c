/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:05:30 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/06 13:45:20 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	glob_logic(t_ms *shell, char **matches, char *pattern)
{
	struct dirent	*entry;
	DIR				*dp;

	dp = opendir(".");
	if (!dp)
		print_error(shell, "minishell: Error opening directory");
	entry = readdir(dp);
	while (entry)
	{
		if (pattern[0] != '.' && entry->d_name[0] == '.')
		{
			entry = readdir(dp);
			continue ;
		}
		if (match(pattern, entry->d_name))
			*matches = replace_cmd(*matches, entry->d_name, shell);
		entry = readdir(dp);
	}
	closedir(dp);
}

void	single_quote(int *i, char **cmd)
{
	int	start;
	int	end;

	start = (*i)++;
	while ((*cmd)[*i] && (*cmd)[*i] != '\'')
		(*i)++;
	end = (*i)--;
	remove_quotes(cmd, start, end);
}

void	double_quote(t_ms *shell, int *i, char **cmd)
{
	int	start;
	int	end;

	start = (*i)++;
	while ((*cmd)[*i] && (*cmd)[*i] != '\"')
	{
		if ((*cmd)[*i] && (*cmd)[*i] == '$' && (*cmd)[*i + 1] != ' ' && (*cmd)[*i + 1] != '\"')
			*i = deal_dollar(cmd, shell, *i + 1);
		else
			(*i)++;
	}
	end = (*i)--;
	remove_quotes(cmd, start, end);
}
