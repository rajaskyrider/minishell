/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:55:29 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/25 10:21:08 by tle-moel         ###   ########.fr       */
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
		ptr = shell->envlst;
		while (ptr)
		{
			if (ft_strncmp(ptr->key, arg[i], ft_strlen(ptr->key)) == 0)
			{
				if (ft_strncmp(ptr->key, "PWD", ft_strlen(ptr->key)) == 0)
					shell->pwd = NULL;
				else if (ft_strncmp(ptr->key, "OLDPWD", ft_strlen(ptr->key)) == 0)
					shell->oldpwd = NULL;
				delete_env_node(&shell->envlst, ptr);
				break ;
			}
			ptr = ptr->next;
		}
		i++;
	}
	shell->env = update_env(shell);
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
