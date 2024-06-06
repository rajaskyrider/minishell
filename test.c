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
		"T_O_PARENT",
		"T_C_PARENT",
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
