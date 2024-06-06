/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:42:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/06 10:13:36 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell> "

# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_AND_IF,
	T_OR_IF,
	T_O_PARENT,
	T_C_PARENT,
	T_DOLLAR,
	T_EXIT_STATUS,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_WILDCARD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_ast_type
{
	T_OPERATOR,
	T_OPERAND
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	t_token_type	token_type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_ms
{
	char	*cmd;
	t_token	*token_lst;
	t_ast	*ast;
}	t_ms;

void	readprompt(t_ms *shell, char *new_cmd);
void	exit_shell(t_ms *shell, int exitcode);
t_token	*create_token_lst(char *cmd_line);
void	tokenize(t_ms *shell);
int		ms_isspace(char c);
int		ms_isquote(char c);
int		ms_isoperator(char *s);
int		ms_isparenthesis(char c);
void	add_token_end_lst(t_token **token_lst, t_token *token);
void	handle_parenthesis(t_token **token_lst, char **cmd_line);
void	handle_operator(t_token **token_lst, char **cmd_line);
void	handle_quote(t_token **token_lst, char **cmd_line);
void	handle_special(t_token **token_lst, char **cmd_line);
void	handle_word(t_token **token_lst, char **cmd_line);
void	delete_token(t_token **token);
void	add_quote_token(t_token **token_lst, char **cmd_line);
void	handle_quote(t_token **token_lst, char **cmd_line);
void	handle_single_quote(t_token **token_lst, char **cmd_line);
void	handle_double_quote(t_token **token_lst, char **cmd_line);
void	process_double_quote(t_token *ptr);
void	exec_replace(char **new_str, char *start, char *end, char *str);
void	parser(t_ms *shell);
void	combine_node(t_ms *shell);
void	process_expr(t_ms *shell);
void	delete_single_quote(t_token **token, t_ms *shell);
void	delete_double_quote(t_token **token, t_ms *shell);
void	delete_token(t_token **token);
t_ast	*precedence_climbing(t_ms *shell, t_token **node, int precedence);
//void	execute_echo(t_ms *shell, char *cmd, char *str);

/*Test functions (to remove)*/
void	print_token_lst(t_ms *shell);
void	print_ast(t_ast *tree, int level);
#endif
