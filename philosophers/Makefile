# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/04/07 17:56:17 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

LIB_DIR = ./libft

SRCS = philo.c \
		ft_utils1.c

# BONUS = pipex_bonus.c ft_pipex_utils_bonus.c

OBJS = $(SRCS:.c=.o)
# OBJS_BONUS = $(BONUS:.c=.o)


%o: %c
	$(CC) -c $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(OBJS)
	$(MAKE) all -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $^
	$(CC) $@ -o philo

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
