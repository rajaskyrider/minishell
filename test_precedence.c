/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_precedence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:20:45 by rpandipe          #+#    #+#             */
/*   Updated: 2024/05/13 16:33:59 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// precedence of + is 1
// precedence of * is 2
// Highest precedence should be run first

int	read_expr(char **expr)
{
	int	n;
	
	n = atoi(*expr);
	(*expr)++;
	while (**expr != '\0' && **expr == ' ')
		(*expr)++;
	return (n);
}

int	parse_expr(char **expr, int precedence)
{
	int	left;
	int	right;
	int	newprecedence;
	char op;

	right = 0;
	left = read_expr(expr);
	while (1)
	{
		if (**expr == 0)
			break;
		op = **expr;
		if (op == '+')
			newprecedence = 1;
		else if (op == '*')
			newprecedence = 2;
		if (newprecedence < precedence)
			break;
		*expr += 2;
		right = parse_expr(expr, newprecedence + 1);
		if (op == '+')
			left += right;
		else if (op == '*')
			left *= right;
	}
	return (left);
}

int	main(void)
{
	char	*expr = "1 + 2 * 3";

	printf("%d\n", parse_expr(&expr, 0));
}