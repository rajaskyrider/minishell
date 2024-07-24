/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:40:53 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/24 11:49:15 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logic_deal_dollar(char **cmd, int start, int *end, char **result)
{
	*result = NULL;
	*end = start;
	while ((*cmd)[*end] && (*cmd)[*end] != ' ' \
			&& (*cmd)[*end] != '$' && \
			(*cmd)[*end] != '\"' && (*cmd)[*end] != '\'')
		(*end)++;
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
