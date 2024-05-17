/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/10 15:46:48 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ms_isoperator(char *s)
{
	if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	if (ft_strncmp(s, "|", 1) == 0)
		return (1);
	if (ft_strncmp(s, "&&", 2) == 0)
		return (1);
	return (0);
}

int	ms_isparenthesis(char c)
{
	if (c == '(' || c == ')')
		return (1);
	return(0);
}

int	ms_isquote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}
