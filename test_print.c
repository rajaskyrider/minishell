/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:42:37 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/25 13:51:37 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_lst(t_ms *shell)
{
	int	i;
	t_token	*token_lst;

	i = 1;
	token_lst = shell->token_lst;
	const char *token_type_str[] = 
	{
		"T_WORD",
		"T_PIPE",
		"T_LESS",
		"T_GREAT",
		"T_DLESS",
		"T_DGREAT",
		"T_AND_IF",
		"T_OR_IF",
		"T_PARENT",
		"T_DOLLAR",
		"T_EXIT_STATUS",
		"T_SINGLE_QUOTE",
		"T_DOUBLE_QUOTE",
		"T_WILDCARD"
	};
	while (token_lst != NULL)
	{
		ft_printf("---- %ith element ----\n", i);
		ft_printf("type : %s\n", token_type_str[token_lst->type]);
		ft_printf("value : %s\n", token_lst->value);
		token_lst = token_lst->next;
		i++;
	}
}


void	print_ast(t_ast *tree, int level) 
{
	const char *token_type_str[] = 
	{
		"T_WORD",
		"T_PIPE",
		"T_LESS",
		"T_GREAT",
		"T_DLESS",
		"T_DGREAT",
		"T_AND_IF",
		"T_OR_IF",
		"T_PARENT",
		"T_DOLLAR",
		"T_EXIT_STATUS",
		"T_SINGLE_QUOTE",
		"T_DOUBLE_QUOTE",
		"T_WILDCARD"
	};
	if (tree == NULL)
		return;
	ft_printf("-----------------------------\n");
	ft_printf("Level %d\n", level);
	if (tree->value)
		ft_printf("Operator %s\n", tree->value);
	else
		ft_printf("Type %s\n", token_type_str[tree->token_type]);
	if (tree->left != NULL)
	{
		if (tree->left->value)
			ft_printf("Left %s",  tree->left->value);
		else
			ft_printf("left %s", token_type_str[tree->left->token_type]);
	}
	ft_printf("\t");
	if (tree->right != NULL)
	{
		if (tree->right->value)
			ft_printf("Right %s",  tree->right->value);
		else
			ft_printf("right %s", token_type_str[tree->right->token_type]);
	}
	ft_printf("\n");
	print_ast(tree->left, level + 1);
	print_ast(tree->right, level + 1);
}