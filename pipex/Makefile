# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/02/17 13:33:51 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar -rcs
RM = rm -f

LIB_DIR = ./libft

SRCS = pipex.c

BONUS = pipex_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)

ifdef WITH_BONUS
    OBJ_FILES = $(OBJS_BONUS)
else
    OBJ_FILES = $(OBJS)
endif

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(OBJ_FILES)
	$(MAKE) all -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $^
	$(CC) $@ -o pipex

all: $(NAME)

bonus:
	make WITH_BONUS=1 all

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
