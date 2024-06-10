/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:55:29 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/10 14:24:09 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(char **arg, t_ms *shell)
{
	int			i;
	t_envlst	*ptr;

	i = 1;
	while (arg[i] != NULL)
	{
		ptr = shell->environ;
		while (ptr)
		{
			if (ft_strncmp(ptr->key, arg[i], ft_strlen(ptr->key)) == 0)
			{
				delete_env_node(&shell->environ, ptr);
				break ;
			}
			ptr = ptr->next;
		}
		i++;
	}
}

void	delete_env_node(t_envlst **head, t_envlst *node)
{
	if (!head || !(*head) || !node)
		return ;
	if (*head == node)
		*head = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->key);
	free(node->value);
	free(node);
}