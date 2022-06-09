# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/06/09 17:57:38 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
AR = ar -rcs
RM = rm -f

SRCS = miniRT.c \
		ft_gnl_utils.c \
		ft_split.c \
		ft_utils2.c \
		get_ambcam.c \
		get_color.c \
		get_coord.c \
		get_double.c \
		get_elem.c \
		get_int.c \
		get_next_line.c \
		ft_init.c \
		calVec.c \
		utils_1.c \
		trace.c \
		cylinder.c


OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(AR) $@ $^
	$(CC) $(CLIB) $(SRCS) $@ -o miniRT -g

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) miniRT

re:
	$(make) fclean
	$(make) all
.PHONY: all clean fclean re
