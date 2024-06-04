/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:35:32 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/04 16:30:48 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *tree)
{
	if (tree == NULL)
		return ;
	ft_printf("%s\n", tree->value);
	ft_printf("left\n");
	print_ast(tree->left);
	ft_printf("right\n");
	print_ast(tree->right);
}

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
	ft_printf("here inside2\n");
	node->left = NULL;
	node->right = NULL;
	ft_printf("here inside\n");
	return (node);
}

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
		left = operator;
	}
	ft_printf("here7\n");
	return (left);
}

// cc test.c | wc -l < text.txt