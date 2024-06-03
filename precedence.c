/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:35:32 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/03 11:21:51 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_precedence(t_token_type op)
{
	if (op == T_O_PARENT || op == T_C_PARENT)
		return (0);
	else if (op == T_LESS || op == T_GREAT || op == T_DLESS || op == T_DGREAT)
		return (1);
	else if (op == T_PIPE)
		return (2);
	else if (op == T_DOLLAR)
		return (3);
	else if (op == T_WILDCARD)
		return (4);
	else
		return (5);
}	

char	*precedence(t_ms *shell, t_token *node, int precedence)
{
	char			*left;
	char			*right;
	int				newprecedence;
	t_token_type	op;

	right = NULL;
	left = node->value;
	node = node->next;
	while (1)
	{
		if (!node)
			break;
		while (node && node->type == T_WORD)
		{
			//calloc here
			ft_strlcat(left, node->value, (ft_strlen(left) + ft_strlen(node->value) + 1));
			node = node->next;
		}
		op = get_precedence(node->type);
		newprecedence = op;
		if (newprecedence < precedence)
			break;
		node = node->next;
		right = precedence(shell, node, newprecedence + 1);
		ft_execute(left, right, op);
	}
	return (left);
}
