/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:42:37 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/06 11:57:32 by rpandipe         ###   ########.fr       */
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


void	logical_or_old(t_ast **ast, t_ms **shell, int next_pipe[2])
{
	int	pid;
	int pidf;
	int	status;

	status = 0;
	dprintf(2, "Status entering logical or %d\n",(*shell)->lexit_status);
	if (!ast || !(*ast))
		return ;
	if ((*ast)->left->type == T_OPERATOR)
	{
		dprintf(2, "Setting up fork for %s and %s\n", (*ast)->left->left->value, (*ast)->left->right->value);
		pid = fork();
		if (pid == 0)
		{
			dprintf(2, "In the child of %s and %s\n", (*ast)->left->left->value, (*ast)->left->right->value);
			navigate(&(*ast)->left, shell, next_pipe);
			dprintf(2, "Done with %s and %s\n", (*ast)->left->left->value, (*ast)->left->right->value);
			exit((*shell)->lexit_status);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			(*shell)->lexit_status = WEXITSTATUS(status);
		dprintf(2, "Status after left fork is %d\n",(*shell)->lexit_status);
	}
		//navigate(&(*ast)->left, shell, next_pipe);
	else if ((*ast)->left->token_type == T_PARENT)
		ms_subshell((*ast)->left, *shell);
	else
		exec_cmd((*ast)->left, (*ast)->left->value, *shell, 0);
	close_fd (*shell);
	dup2((*shell)->std_in, STDIN_FILENO);
	dup2((*shell)->std_out, STDOUT_FILENO);
	if ((*shell)->lexit_status != 0)
	{
		if ((*ast)->right->type == T_OPERATOR)
		{
			//(*shell)->lexit_status = 0;
			dprintf(2, "Setting up fork for %s and %s\n", (*ast)->right->left->value, (*ast)->right->right->value);
			pid = fork();
			if (pid == 0)
			{
				dprintf(2, "in the child of %s and %s\n", (*ast)->right->left->value, (*ast)->right->right->value);
				navigate(&(*ast)->right, shell, next_pipe);
				dprintf(2, "Done with %s and %s\n", (*ast)->right->left->value, (*ast)->right->right->value);
				pidf = wait(&status);
				while (pidf > 0)
				{
					signal_process();
					if (WIFEXITED(status))
						(*shell)->lexit_status = WEXITSTATUS(status);
					dprintf(2, "Terminated\n");
					pidf = wait(&status);
				}
				exit((*shell)->lexit_status);
			}
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				(*shell)->lexit_status = WEXITSTATUS(status);
			dprintf(2, "Status after right fork is %d\n",(*shell)->lexit_status);
		}
		else if ((*ast)->right->token_type == T_PARENT)
			ms_subshell((*ast)->right, *shell);
		else
			exec_cmd((*ast)->right, (*ast)->right->value, *shell, 0);
		close_fd (*shell);
	}
	else if ((*shell)->lexit_status == 0 && \
		(*ast)->right->token_type == T_AND_IF)
	{
		if ((*ast)->right->right->type == T_OPERATOR)
			navigate(&(*ast)->right->right, shell, next_pipe);
		else if ((*ast)->right->right->token_type == T_PARENT)
			ms_subshell((*ast)->right->right, *shell);
		else
			exec_cmd((*ast)->right->right, (*ast)->right->right->value, *shell, 0);
		close_fd (*shell);
	}
}