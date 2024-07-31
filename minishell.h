/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:42:50 by rpandipe          #+#    #+#             */
/*   Updated: 2024/07/31 13:56:26 by rpandipe         ###   ########.fr       */
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
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>

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
	T_PARENT,
	T_EXIT_STATUS,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE
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
	char			*key;
	char			*value;
	struct s_envlst	*next;
	struct s_envlst	*prev;
}	t_envlst;

typedef struct s_ms
{
	char		*cmd;
	t_token		*token_lst;
	t_ast		*ast;
	char		**env;
	t_envlst	*envlst;
	int			error;
	int			lexit_status;
	//int			pip[2];
	int			io_in;
	int			io_out;
	int			std_in;
	int			std_out;
	pid_t		pid;
	char		*pwd;
	char		*oldpwd;
}	t_ms;

void		init_shell(t_ms *shell, char **env);
void		ms_cd(t_ms *shell, char **path);
void		ms_echo(char **arg);
void		ms_env(t_ms *shell);
void		ms_exit(char **arg, t_ms *shell);
void		ms_export(char **arg, t_ms *shell);
void		ms_pwd(t_ms *shell);
void		ms_unset(char **arg, t_ms *shell);
char		*extract_key(char *env_line);
char		*extract_value(char *env_line);
void		update_envlst(char *key, char *value, t_envlst **environ);
void		add_node_envlst(char *key, char *value, t_envlst **environ);
t_envlst	*init_envlst(char **env);
int			key_is_valid(char *key);
char		*find_min_key(t_envlst *environ);
char		*find_next_key(char *curr_key, t_envlst *environ);
void		readprompt(t_ms *shell, char *new_cmd);
void		exit_shell(t_ms *shell, int exitcode);
t_token		*create_token_lst(char *cmd_line, t_ms *shell);
int			tokenize(t_ms *shell);
int			ms_isspace(char c);
int			ms_isquote(char c);
int			ms_isoperator(char *s);
int			ms_isparenthesis(char c);
int			ms_isredirect(t_token_type t);
void		add_token_end_lst(t_token **token_lst, t_token *token);
int			handle_parenthesis(t_token **token_lst, \
								char **cmd_line, t_ms *shell);
char		*handle_subshell(t_token **token_lst, char **cmd_line);
int			handle_operator(t_token **token_lst, char **cmd_line);
int			handle_quote(t_token **token_lst, char **cmd_line);
int			handle_word(t_token **token_lst, char **cmd_line);
void		delete_token(t_token **token);
void		add_quote_token(t_token **token_lst, char **cmd_line);
int			handle_single_quote(int *i, char **cmd_line);
int			handle_double_quote(int *i, char **cmd_line);
void		process_double_quote(t_token *ptr);
void		exec_replace(char **new_str, char *start, char *end, char *str);
int			parser(t_ms *shell);
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
void		delete_ast_lst(t_ast **ast);
void		delete_env_lst(t_envlst **environ);
int			init_token(t_token **token);
t_ast		*precedence_climbing(t_ms *shell, t_token **node, int precedence);
void		clear_shell(t_ms *shell);
int			ms_strcmp(char *s1, char *s2);
void		print_error(t_ms *shell, char *errormsg);
char		*extract_key(char *env_line);
char		*extract_value(char *env_line);
void		check_cmd(t_ms *shell);
void		print_export(t_envlst *environ);
void		delete_env_node(t_envlst **head, t_envlst *node);
void		update_pwd(t_ms *shell);
char		*get_path(t_ms *shell);
void		exec_cmd(t_ast *ast, char *full_cmd, t_ms *shell, int flag);
void		navigate(t_ast **ast, t_ms **shell, int next_pipe[2]);
void		execute_simple(t_ms *shell);
void		exec_given_path(char *full_cmd, t_ms *shell, char **args);
int			is_builtin(char *full_cmd, t_ms *shell, char **arg);
int			path_is_given(char *full_cmd);
char		**find_paths(t_envlst *environ);
char		*get_cmd(char *cmd, char **paths, t_ms *shell);
char		**split_and_expand(char *full_cmd, t_ms *shell);
int			deal_redirection(t_ast *ast, t_ms *shell);
void		execute(t_ms *shell);
int			glob(char **cmd, t_ms *shell, int start);
int			check_redirection(t_ast *ast, t_ms **shell);
void		check_directory(char *cmd, t_ms *shell);
void		ms_pipe(t_ast *ast, t_ms **shell, int pipe_fd[2], int last_pipe[2]);
void		sync_heredoc(t_ast *ast, int pid, t_ms *shell);
void		check_here_doc(char *limiter, int *fd, t_ms *shell);
void		close_pipe(int pip[2]);
char		*expandcmd(char *cmd, t_ms *shell);
char		*replace_wildcard(char *cmd, char *matches, int start, t_ms *shell);
int			deal_dollar(char **cmd, t_ms *shell, int start);
int			find_start(char *cmd, int start);
void		remove_quotes(char **cmd, int start, int end);
char		**ms_split(char const *s, char c);
void		setup_pipe(int pip[2], t_ms **shell);
void		deal_logical(t_ast **ast, t_ms **shell, int next_pipe[2]);
void		close_fd(t_ms *shell);
void		handle_sigint(int sig);
void		handle_sigint_process(int sig);
void		handle_sigquit_process(int sig);
void		init_signal(void);
void		signal_process(void);
char		**init_env(char **env);
void		clean_env(char	**env);
int			count_env_elements(t_envlst *environ);
char		**update_env(t_ms *shell);
long long	ft_atoll(const char *nptr);
void		clean_shell(t_ms *shell);
void		check_syntax_error(t_ms *shell);
int			initial_check(t_token *ptr, t_ms *shell);
int			first_check(t_token *ptr, t_ms *shell);
int			second_check(t_token *ptr, t_ms *shell);
int			third_check(t_token *ptr, t_ms *shell);
int			fourth_check(t_token *ptr, t_ms *shell);
void		err_mss_heredoc(void);
int			less_or_great(t_ms **shell, int *fd, t_io *ptr);
int			handle_dgreat(t_ms **shell, int *fd, t_io *ptr);
void		logic_deal_dollar(char **cmd, int start, int *end, char **result);
int			check_question(char **cmd, t_ms *shell, int start);
void		glob_logic(t_ms *shell, char **matches, char *pattern);
int			match(char *pattern, char *filename);
char		*replace_cmd(char *cmd, char *filename, t_ms *shell);
void		single_quote(int *i, char **cmd);
void		double_quote(t_ms *shell, int *i, char **cmd);
char		*get_shellpwd(t_ms *shell);
void		update_shelloldpwd(t_ms *shell);
void		ms_subshell(t_ast *ast, t_ms *shell);
void		free_args(char **args);

/*Test functions (to remove)*/
void		print_token_lst(t_ms *shell);
void		print_ast(t_ast *tree, int level);
#endif
