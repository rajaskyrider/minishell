# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:30:56 by rpandipe          #+#    #+#              #
#    Updated: 2024/06/03 17:05:14 by tle-moel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a
CC			= cc
CFLAG		= -Wall -Werror -Wextra -g
LFLAG		= -Llibft -lft
RM 			= rm -rf
SRCS		= main.c prompt.c tokenize.c tokenize_handle.c tokenize_utils.c \
			  tokenize_quote.c test.c utils.c parser.c
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
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAG) -c $< -o $@ > /dev/null 2>&1
	$(call update_progress)

$(NAME): $(OBJS)
	@echo -e '${YELLOW}Linking...${NC}'
	@$(CC) $(OBJS) $(LFLAG) -lreadline -pthread -o $(NAME) > /dev/null 2>&1
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
