# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/05/28 09:44:07 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
AR = ar -rcs
RM = rm -f

SRCS = cub3d.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(AR) $@ $^
	$(CC) $(CLIB) $(SRCS) $@ -o cub3d

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) cub3d

re: fclean all

.PHONY: all clean fclean re
