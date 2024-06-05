/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:35:32 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/05 18:29:28 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *tree, int level) 
{
	int	i;

	i = -1;
	if (tree == NULL)
		return;
	if (tree->right != NULL)
		print_ast(tree->right, level + 1);
	while (++i < level)
		ft_printf("    ");
	ft_printf("%s\n", tree->value);
	if (tree->left != NULL)
		print_ast(tree->left, level + 1);
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
# if 0
t_ast	*precedence_climbing(t_ms *shell, t_token *node, int precedence)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*operator;
	int				newprecedence;
	t_token_type	op;

	right = NULL;
	left = create_ast(T_OPERAND, node->value, node->type, shell);
	ft_printf("here\n");
	node = node->next;
	ft_printf("here2\n");
	while (node)
	{
		op = get_precedence(node->type);
		ft_printf("here3\n");
		operator = create_ast(T_OPERATOR, "operator", node->type, shell);
		ft_printf("here4\n");
		newprecedence = op;
		if (newprecedence < precedence)
			break;
		node = node->next;
		if (!node)
			break;
		ft_printf("here5\n");
		right = precedence_climbing(shell, node, newprecedence + 1);
		ft_printf("here6\n");
		operator->left = left;
		operator->right = right;
		node = node->next;
		if (node)
			left = create_ast(T_OPERAND, node->value, node->type, shell);
	}
	ft_printf("here7\n");
	return (left);
}
#endif

#if 1
t_ast	*precedence_climbing(t_ms *shell, t_token **pnode, int min_precedence)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*new_op;

	if (!*pnode)
		return (NULL);

	left = create_ast(T_OPERAND, (*pnode)->value, (*pnode)->type, shell);
	*pnode = (*pnode)->next;

	while (*pnode)
	{
		int curr_precedence = get_precedence((*pnode)->type);
		if (curr_precedence < min_precedence)
			break;

		t_token *operator_token = *pnode;
		*pnode = (*pnode)->next;  // Move past the operator token

		// Recurse with higher precedence to evaluate the right subtree
		right = precedence_climbing(shell, pnode, curr_precedence + 1);

		// Create an operator node that combines the left and right subtrees
		new_op = create_ast(T_OPERATOR, "operator", operator_token->type, shell);
		new_op->left = left;
		new_op->right = right;
		left = new_op;  // The new operator becomes the new 'left' subtree
	}

	return left;
}

#endif

// cc test.c | wc -l < text.txt