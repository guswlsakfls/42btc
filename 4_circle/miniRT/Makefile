# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/05/31 18:58:43 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
AR = ar -rcs
RM = rm -f

SRCS = miniRT.c \
		utils_1.c \
		trace.c \
		calVec.c \
		ft_init.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(AR) $@ $^
	$(CC) $(CLIB) $(SRCS) $@ -o miniRT

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) miniRT

re: fclean all

.PHONY: all clean fclean re
