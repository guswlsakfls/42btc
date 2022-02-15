# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/02/15 14:29:50 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar -rcs
RM = rm -f

LIB_DIR = ./libft

SRCS = pipex.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(OBJS)
	$(MAKE) all -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $^
	$(CC) $@ -o pipex

all: $(NAME)

bonus : all

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
