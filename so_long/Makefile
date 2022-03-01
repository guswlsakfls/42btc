# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/03/01 15:50:07 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
AR = ar -rcs
RM = rm -f

SRCS = so_long.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_utils.c \
		ft_init.c \
		ft_move.c \
		ft_parsing_map.c \
		ft_printf_map.c \

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(AR) $@ $^
	$(CC) $(CLIB) $(SRCS) $@ -o so_long

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) so_long

re: fclean all

.PHONY: all clean fclean re
