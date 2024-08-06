# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:30:56 by rpandipe          #+#    #+#              #
#    Updated: 2024/08/06 15:56:40 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a
CC			= cc
CFLAG		= -Wall -Werror -Wextra -g -I.
LFLAG		= -Llibft -lft
RM 			= rm -rf
BUILTIN		= builtin/ms_cd.c builtin/ms_echo.c builtin/ms_env_utils.c \
			  builtin/ms_env.c builtin/ms_exit.c builtin/ms_export_utils.c \
			  builtin/ms_export.c builtin/ms_pwd.c builtin/ms_unset.c \
			  builtin/update_shellpwd.c
TOKENIZER	= tokenizer/tokenize.c tokenizer/tokenize_handle.c \
			  tokenizer/tokenize_utils.c tokenizer/tokenize_quote.c \
			  tokenizer/tokenize_syntax.c
PARSER		= parser/parser.c parser/parser_utils.c parser/precedence.c \
			  parser/parser_check.c parser/deal_io.c
EXEC		= exec/exec_cmd.c exec/navigate.c exec/glob.c \
			  exec/ms_pipe.c exec/dollar.c exec/ms_redirection.c \
			  exec/exec_setup.c exec/exec_utils.c exec/logical_op.c \
			  exec/handle_redirection.c exec/dollar_utils.c exec/glob_utils.c \
			  exec/ms_subshell.c exec/pipe_utils.c exec/sort_cmd.c
SRCS		= main.c prompt.c utils.c validation.c clean.c ms_split.c signals.c env.c ft_atoll.c test_print.c\
			  $(BUILTIN) \
			  $(TOKENIZER) \
			  $(PARSER) \
			  $(EXEC) \
			  $(TEST)
OBJDIR      = objs
OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
TOTAL       = $(words $(OBJS))
CURRENT     = 0

# ANSI color codes
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
RED         = \033[0;31m
NC          = \033[0m

define update_progress
$(eval CURRENT=$(shell echo $$(($(CURRENT) + 1))))
@echo -ne '${GREEN}Building... [$(CURRENT)/$(TOTAL)]${NC}\r'
endef

all: $(NAME)
	@echo -e '${BLUE}Build complete!${NC}'

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) -c $< -o $@ 
	$(call update_progress)

$(NAME): $(OBJS)
	@make -C libft > /dev/null 2>&1
	@cp libft/$(LIBFT) .
	@$(CC) $(OBJS) $(CFLAG) $(LIBFT) -lreadline -pthread -o $(NAME)
	@echo -ne '\n'

clean:
		@cd libft && $(MAKE) clean > /dev/null 2>&1
		@$(RM) $(OBJDIR) > /dev/null 2>&1
		@echo -e '${RED}Clean complete!${NC}'

fclean:	clean
		@cd libft && $(MAKE) fclean > /dev/null 2>&1
		@$(RM) $(NAME) > /dev/null 2>&1
		@echo -e '${RED}Build deleted!${NC}'
		@echo -ne '\n'

re: fclean all

.PHONY: all clean fclean re
