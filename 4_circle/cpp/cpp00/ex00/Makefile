# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 13:14:06 by hyujo             #+#    #+#              #
#    Updated: 2022/05/03 18:15:31 by hyujo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = megaphone
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = megaphone.cpp

$(NAME): $(SRCS)
	$(CXX) $^ $(CXXFLAGS) -o $@

all : $(NAME)

clean:
	rm -rf $(NAME)

fclean : clean

re:	clean all

.PHONY: all clean fclean re
