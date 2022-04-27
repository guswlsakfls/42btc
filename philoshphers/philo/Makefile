# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/04/27 22:23:47 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar -rcs
RM = rm -f

SRCS = philo.c \
		ft_philo_routine.c \
		ft_utils1.c \
		ft_utils2.c \
		ft_init.c \
		ft_eat.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

$(NAME): $(OBJS)
	$(AR) $@ $^
	$(CC) -lpthread $@ -o philo

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
