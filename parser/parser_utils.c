/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:26:17 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/23 17:45:44 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_io(t_token *new, t_token *old)
{
	t_io	*ptr;

	ptr = new->io;
	if (!ptr)
	{
		new->io = old->io;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = old->io;
}

void	concat_node(t_token *tkn, t_ms *shell)
{
	t_token	*ptr;
	char	*result;
	int		len;

	ptr = tkn;
	len = ft_strlen(ptr->value) + ft_strlen(ptr->next->value) + 2;
	result = ft_calloc(len, sizeof(char));
	if (!result)
		exit_shell(shell, EXIT_FAILURE);
	ft_strlcpy(result, ptr->value, len);
	ft_strlcat(result, " ", len);
	ft_strlcat(result, ptr->next->value, len);
	free(ptr->value);
	ptr->value = result;
	if (ptr->next->io)
		concat_io(ptr, ptr->next);
	delete_token(&(ptr->next));
}

void	combine_node(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	while (ptr)
	{
		if (ptr->next && ptr->type == T_WORD && ptr->next->type == T_WORD)
			concat_node(ptr, shell);
		else
			ptr = ptr->next;
	}
}
