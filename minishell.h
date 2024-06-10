/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:42:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/10 13:51:29 by tle-moel         ###   ########.fr       */
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

typedef struct s_io
{
	t_token_type	type;
	char			*value;
	struct s_io		*next;
	struct s_io		*prev;
}	t_io;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
	t_io			*io;
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
	t_io			*io;
}	t_ast;

typedef struct s_envlst
{
	char	*key;
	char	*value;
	struct s_envlst	*next;
	struct s_envlst	*prev;
}	t_envlst;


typedef struct s_ms
{
	char	*cmd;
	t_token	*token_lst;
	t_ast	*ast;
	t_envlst	*environ;
	int		error;
}	t_ms;

void		readprompt(t_ms *shell, char *new_cmd);
void		exit_shell(t_ms *shell, int exitcode);
t_token		*create_token_lst(char *cmd_line, t_ms *shell);
void		tokenize(t_ms *shell);
int			ms_isspace(char c);
int			ms_isquote(char c);
int			ms_isoperator(char *s);
int			ms_isparenthesis(char c);
int			ms_isreorder(t_token_type t);
void		add_token_end_lst(t_token **token_lst, t_token *token);
int			handle_parenthesis(t_token **token_lst, char **cmd_line);
int			handle_operator(t_token **token_lst, char **cmd_line);
int			handle_quote(t_token **token_lst, char **cmd_line);
int			handle_special(t_token **token_lst, char **cmd_line);
int			handle_word(t_token **token_lst, char **cmd_line);
void		delete_token(t_token **token);
void		add_quote_token(t_token **token_lst, char **cmd_line);
int			handle_single_quote(t_token **token_lst, char **cmd_line);
int			handle_double_quote(t_token **token_lst, char **cmd_line);
void		process_double_quote(t_token *ptr);
void		exec_replace(char **new_str, char *start, char *end, char *str);
void		parser(t_ms *shell);
void		concat_node(t_token *tkn, t_ms *shell);
void		combine_node(t_ms *shell);
void		check_reorder(t_ms *shell);
void		deal_io(t_ms *shell);
void		create_io(t_token *ptr, t_ms *shell);
void		process_expr(t_ms *shell);
void		delete_single_quote(t_token **token, t_ms *shell);
void		delete_double_quote(t_token **token, t_ms *shell);
void		delete_token(t_token **token);
void		delete_token_lst(t_token **token);
int			init_token(t_token **token);
t_ast		*precedence_climbing(t_ms *shell, t_token **node, int precedence);
void		ms_echo(char **arg);
void		clear_shell(t_ms *shell);
void		print_error(t_ms *shell, char *errormsg);
void		ms_env(t_ms *shell);
t_envlst	*init_environ(char **env);
char		*extract_key(char *env_line);
char		*extract_value(char *env_line);
void		update_envlst(char *key, char *value, t_envlst **environ);
void		check_cmd(t_ms *shell);
void		ms_export(char **arg, t_ms *shell);
void		print_export(t_envlst *environ);
char		*find_min_key(t_envlst *environ);
char		*find_next_key(char *curr_key, t_envlst *environ);
void		ms_unset(char **arg, t_ms *shell);
void		delete_env_node(t_envlst **head, t_envlst *node);
/*Test functions (to remove)*/
void		print_token_lst(t_ms *shell);
void		print_ast(t_ast *tree, int level);
#endif
