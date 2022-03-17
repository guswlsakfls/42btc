# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/03/17 12:34:20 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar -rcs
RM = rm -f

LIB_DIR = ./libft

RL_DIR = $(shell brew --prefix readline)
RL_INC = $(RL_DIR)/include
RL_LIB = $(RL_DIR)/lib

SRCS = minishell.c \
		ft_redirection.c \
		analyze.c \
		tokenize.c \
		tokenize_utils.c

SRCS_TEST = ./testFile/redir_right.c \
			./testFile/test_utils.c \
			analyze.c \
			tokenize.c \
			tokenize_utils.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) -I $(RL_INC) $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(OBJS)
	$(MAKE) bonus -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $^
	$(CC) -L$(RL_LIB) -lreadline -lhistory $@ -o minishell

all: $(NAME)

# 테스트 해보려고 만듬
test :
	gcc -I. -lreadline -lhistory -L$(RL_LIB) -I$(RL_INC) $(SRCS_TEST) ./testFile/libft/*.c -g

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
