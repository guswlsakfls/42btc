# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scha <scha@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/06/16 20:25:56 by scha             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT.a
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
CLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
AR = ar -rcs
RM = rm -f

SRCS = miniRT.c \
		get_next_line_utils.c \
		ft_split.c \
		ft_utils.c \
		ft_utils2.c \
		ft_utils3.c \
		get_ambcam.c \
		get_color.c \
		get_coord.c \
		get_double.c \
		get_elem.c \
		get_int.c \
		get_next_line.c \
		ft_init.c \
		calVec.c \
		calVec2.c \
		calVec3.c \
		calVec4.c \
		utils_1.c \
		trace.c \
		trace2.c \
		ray_init.c \
		cylinder.c \
		phong_light.c


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

re:
	make fclean
	make all
.PHONY: all clean fclean re
