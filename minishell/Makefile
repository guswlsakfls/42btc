# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/03/21 23:51:24 by hyunjinjo        ###   ########.fr        #
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
		parser_tokenize.c \
		parser_tokenize_utils.c \
		parser_merge.c \
		parser_analyze.c \
		parser_analyze_utils.c \
		parser_merge_utils.c \
		ft_redirection.c \

SRCS_TEST = ./testFile/heredoc_test.c \
			# ./testFile/test_utils.c \
			# ./testFile/analyze.c \
			# ./testFile/tokenize.c \
			# ./testFile/tokenize_utils.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) -I $(RL_INC) $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $^
	$(CC) -L$(RL_LIB) -lreadline -lhistory $@ -o minishell

all: $(NAME)

# 테스트 해보려고 만듬
test :
	gcc -ItestFile/*.h -lreadline -lhistory -L$(RL_LIB) -I$(RL_INC) $(SRCS_TEST) ./testFile/libft/*.c -g

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
