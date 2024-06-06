/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:35:32 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/06 10:08:43 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *tree, int level) 
{
	if (tree == NULL)
		return;
	ft_printf("-----------------------------\n");
	ft_printf("Level %d\n", level);
	ft_printf("Operator %s\n", tree->value);
	if (tree->left != NULL)
		ft_printf("Left %s",  tree->left->value);
	ft_printf("\t");
	if (tree->right != NULL)
		ft_printf("Right %s",  tree->right->value);
	ft_printf("\n");
	print_ast(tree->left, level + 1);
	print_ast(tree->right, level + 1);
}

int	get_precedence(t_token_type op)
{
	if (op == T_O_PARENT || op == T_C_PARENT)
		return (5);
	else if (op == T_LESS || op == T_GREAT || op == T_DLESS || op == T_DGREAT)
		return (4);
	else if (op == T_PIPE)
		return (3);
	else if (op == T_AND_IF)
		return (2);
	else if (op == T_OR_IF)
		return (1);
	else if (op == T_WILDCARD)
		return (0);
	else
		return (-1);
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
	//ft_printf("here inside2\n");
	node->left = NULL;
	node->right = NULL;
	//ft_printf("here inside\n");
	return (node);
}

t_ast	*precedence_climbing(t_ms *shell, t_token **pnode, int min_precedence)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*new_op;
	t_token	*operator_token;
	int		curr_precedence;

	if (!*pnode)
		return (NULL);
	left = create_ast(T_OPERAND, (*pnode)->value, (*pnode)->type, shell);
	*pnode = (*pnode)->next;
	while (*pnode)
	{
		curr_precedence = get_precedence((*pnode)->type);
		if (curr_precedence < min_precedence)
			break;
		operator_token = *pnode;
		*pnode = (*pnode)->next;  
		right = precedence_climbing(shell, pnode, curr_precedence + 1);
		new_op = create_ast(T_OPERATOR, "operator", operator_token->type, shell);
		new_op->left = left;
		new_op->right = right;
		left = new_op;
	}
	return left;
}
