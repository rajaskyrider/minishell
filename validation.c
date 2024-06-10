/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:48:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/10 11:00:52 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isreorder(t_token_type t)
{
	return (t == T_LESS \
		|| t == T_GREAT \
		|| t == T_DLESS \
		|| t == T_DGREAT);
}

void	check_reorder(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	while (ptr->next)
	{
		if (ms_isreorder(ptr->type) && ms_isreorder(ptr->next->type))
		{
			print_error(shell, "minishell: Syntax Error");
			break;
		}
		ptr = ptr->next;
	}
	if (ms_isreorder(ptr->type))
		print_error(shell, "minishell: Syntax Error");
}
