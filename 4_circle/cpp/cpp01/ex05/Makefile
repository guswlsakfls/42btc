# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 13:14:06 by hyujo             #+#    #+#              #
#    Updated: 2022/05/23 16:19:37 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = harl
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror
VERSION = -std=c++98

SRCS = main.cpp \
		Harl.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(VERSION) $^ -o $@

all : $(NAME)

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re:	clean all

.PHONY: all clean fclean re
