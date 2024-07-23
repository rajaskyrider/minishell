/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:24:44 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/23 16:43:02 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initial_check(t_token *ptr, t_ms *shell)
{
	if (ptr && ptr->type == T_WORD && ptr->value[0] == '*')
	{
		shell->error = 1;
		shell->lexit_status = 127;
		ft_putstr_fd("minishell: command not found\n", 2);
		return (1);
	}
	else if (ptr && (ptr->type == T_AND_IF || ptr->type == T_OR_IF || \
		ptr->type == T_PIPE))
	{
		shell->error = 1;
		shell->lexit_status = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (1);
	}
	return (0);
}

int	first_check(t_token *ptr, t_ms *shell)
{
	if (ptr->type == T_AND_IF || ptr->type == T_OR_IF || \
			ptr->type == T_PIPE)
	{
		if (!ptr->next || ptr->next->type == T_AND_IF || \
			ptr->next->type == T_OR_IF || ptr->next->type == T_PIPE)
		{
			shell->error = 1;
			shell->lexit_status = 2;
			ft_putstr_fd("minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token\n", 2);
			return (1);
		}
	}
	return (0);
}

int	second_check(t_token *ptr, t_ms *shell)
{
	if (ptr->type == T_GREAT || ptr->type == T_DGREAT || \
			ptr->type == T_LESS || ptr->type == T_DLESS)
	{
		if (!ptr->next || ptr->next->type == T_AND_IF || \
			ptr->next->type == T_OR_IF || ptr->next->type == T_PIPE || \
			ptr->next->type == T_GREAT || ptr->next->type == T_DGREAT || \
			ptr->next->type == T_LESS || ptr->next->type == T_DLESS)
		{
			shell->error = 1;
			shell->lexit_status = 2;
			ft_putstr_fd("minishell: syntax error near ", 2);
			ft_putstr_fd("unexpected token\n", 2);
			return (1);
		}
	}
	return (0);
}

int	third_check(t_token *ptr, t_ms *shell)
{
	if (ptr->next && (ptr->type == T_GREAT || ptr->type == T_DGREAT || \
			ptr->type == T_LESS))
	{
		if (ptr->next->type == T_WORD && \
			ptr->next->value[0] == '*' && ptr->next->value[1] == '\0')
		{
			shell->error = 1;
			shell->lexit_status = 1;
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (1);
		}
	}
	return (0);
}

int	fourth_check(t_token *ptr, t_ms *shell)
{
	if (ptr->next && ptr->type == T_DLESS)
	{
		if (ptr->next->type == T_WORD && \
			ptr->next->value[0] == '*' && ptr->next->value[1] == '\0')
		{
			shell->error = 1;
			shell->lexit_status = 0;
			ft_putstr_fd("minishell: here-document at line 1 ", 2);
			ft_putstr_fd("delimited by end-of-file (wanted `*\')\n", 2);
			return (1);
		}
	}
	return (0);
}
