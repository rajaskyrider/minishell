# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:30:56 by rpandipe          #+#    #+#              #
#    Updated: 2024/05/10 15:36:28 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a
CC			= cc
CFLAG		= -Wall -Werror -Wextra -g
RM 			= rm -rf
SRCS		= main.c prompt.c tokenize.c tokenize_handle.c tokenize_utils.c test.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	cp libft/$(LIBFT) .
	$(CC) $(OBJS) $(LIBFT) -lreadline -pthread -o $(NAME)

clean:
		cd libft && $(MAKE) clean
		$(RM) $(OBJS)

fclean:	clean
		cd libft && $(MAKE) fclean
		$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
