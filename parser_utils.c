/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:26:17 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/06 15:44:59 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	create_io(t_token *ptr, t_ms *shell)
{
	t_io	*io;
	t_io	*pio;

	pio = ptr->io;
	io = ft_calloc(sizeof(t_io), 1);
	if (!io)
		exit_shell(shell, EXIT_FAILURE);
	if (pio)
	{
		while (pio)
			pio = pio->next;
	}
	pio = io;
	ft_printf("\n%s\n", ptr->value);
	io->type = ptr->next->type;
	io->value = ft_strdup(ptr->next->next->value);
	io->next = NULL;
	io->prev = NULL;
	ft_printf("Created\n");
	delete_token(&ptr->next);
	delete_token(&ptr->next);
}

void	deal_io(t_ms *shell)
{
	t_token	*ptr;

	ptr = shell->token_lst;
	while (ptr && ptr->next)
	{
		if (ptr->next->type == T_LESS || ptr->next->type == T_GREAT || ptr->next->type == T_DLESS \
								|| ptr->next->type == T_DGREAT)
			{
				create_io(ptr, shell);
				ft_printf("\n%s\n", ptr->io->value);
			}
		else
			ptr = ptr->next;
	}
}