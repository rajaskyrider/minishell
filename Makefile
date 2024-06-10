# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:30:56 by rpandipe          #+#    #+#              #
#    Updated: 2024/06/10 11:15:31 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a
CC			= cc
CFLAG		= -Wall -Werror -Wextra -g -I.
LFLAG		= -Llibft -lft
RM 			= rm -rf
BUILTIN		= builtin/ms_echo.c builtin/ms_env.c builtin/ms_export.c \
			  builtin/ms_unset.c
TOKENIZER	= tokenizer/tokenize.c tokenizer/tokenize_handle.c \
			  tokenizer/tokenize_utils.c tokenizer/tokenize_quote.c
PARSER		= parser/parser.c parser/parser_utils.c parser/precedence.c \
			  parser/parser_check.c
TEST		= test/test.c
SRCS		= main.c prompt.c utils.c validation.c \
			  $(BUILTIN) \
			  $(TOKENIZER) \
			  $(PARSER) \
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
	@echo -e '${YELLOW}Linking...${NC}'
	@$(CC) $(OBJS) $(LFLAG) -lreadline -pthread -o $(NAME)
	@echo -ne '\n'

clean:
		@$(RM) $(OBJDIR) > /dev/null 2>&1
		@echo -e '${RED}Clean complete!${NC}'

fclean:	clean
		@$(RM) $(NAME) > /dev/null 2>&1
		@echo -e '${RED}Build deleted!${NC}'
		@echo -ne '\n'

re: fclean all

.PHONY: all clean fclean re
