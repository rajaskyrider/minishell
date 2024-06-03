/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:35:32 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/03 16:52:54 by rpandipe         ###   ########.fr       */
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

t_ast	*create_ast(t_ast_type type, char *value, t_token_type token, t_ms *shell)
{
	t_ast	*node;

	node = ft_calloc(sizeof(t_ast), 1);
	if (!node)
		exit_shell(shell, EXIT_FAILURE);
	node->type = type;
	node->value = ft_strdup(value);
	node->token_type = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*precedence(t_ms *shell, t_token *node, int precedence)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*operator;
	int				newprecedence;
	t_token_type	op;

	right = NULL;
	left = create_ast(T_OPERAND, node->value, node->type, shell);
	node = node->next;
	while (node)
	{
		op = get_precedence(node->type);
		operator = create_ast(T_OPERATOR, node->value, node->type, shell);
		newprecedence = op;
		if (newprecedence < precedence)
			break;
		node = node->next;
		if (!node)
			break;
		right = precedence(shell, node, newprecedence + 1);
		operator->left = left;
		operator->right = right;
		left = operator;
	}
	return (left);
}

// cc test.c | wc -l < text.txt