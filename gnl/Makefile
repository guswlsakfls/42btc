# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 11:39:10 by hyujo             #+#    #+#              #
#    Updated: 2021/12/16 13:13:27 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

CC = gcc -g
#  -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=1
AR = ar -rcs
RM = rm -f

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
