# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 11:39:10 by hyujo             #+#    #+#              #
#    Updated: 2021/12/21 18:02:35 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

LIB_DIR = ./libft

SRCS = ft_printf.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) all -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $<
	$(CC) $@

all: $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
