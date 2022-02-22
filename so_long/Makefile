# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/02/22 18:05:48 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

LIB_DIR = ./libft

SRCS = so_long.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(OBJ_FILES)
	$(MAKE) all -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $^
	$(CC) $@ -o so_long

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
