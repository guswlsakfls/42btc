# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/02/26 17:54:40 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx -g
# AR = ar -rcs
RM = rm -f

SRCS = so_long.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_utils.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	# $(AR) $@ $^
	$(CC) $(CLIB) $(CLIB) $(SRCS) -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) so_long.a

re: fclean all

.PHONY: all clean fclean re
