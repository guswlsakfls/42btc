# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by hyujo             #+#    #+#              #
#    Updated: 2022/03/30 09:59:32 by dha              ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
NAME = minishell

LIBFT_DIR = ./libft
LIBFT_NAME = ft
LIBFT = $(LIBFT_DIR)/lib$(LIBFT_NAME).a

RL_DIR = $(shell brew --prefix readline)
RL_INC = $(RL_DIR)/include
RL_LIB = $(RL_DIR)/lib

SRCS = minishell.c \
		parser_analyze.c \
		parser_analyze_utils.c \
		parser_tokenize.c \
		parser_tokenize_utils.c \
		parser_merge.c \
		parser_merge_utils.c \
		parser_optimize.c \
		parser_optimize_utils.c \
		ft_built_in.c \
		ft_redirection.c \
		ft_signal.c \
		ft_env.c \
		ft_excute.c \
		ft_nanoshell.c \
		ft_parent_child.c \
		builtin_env.c \
		builtin_export.c \
		builtin_export_arg.c \
		builtin_export_no_arg.c \
		builtin_echo.c \
		builtin_unset.c \
		builtin_cd.c \
		builtin_pwd.c \
		builtin_exit.c \
		builtin_utils.c \
		builtin_errors.c
INCS = minishell.h
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))


SRCS_TEST = ./testFile/heredoc_test.c \
			# ./testFile/test_utils.c \
			# ./testFile/analyze.c \
			# ./testFile/tokenize.c \
			# ./testFile/tokenize_utils.c

%o: %c
	$(CC) -c $(CFLAGS) -I $(RL_INC) $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(LIBFT) $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) $(OBJS) \
	-L $(LIBFT_DIR) -l$(LIBFT_NAME) \
	-L $(RL_LIB) -lreadline -lhistory -o $@
	@printf "💡 Make $(NAME) Done\n"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(RL_INC) -c $< -o $@ -g

all: $(NAME)

# 테스트 해보려고 만듬
test :
	gcc -ItestFile/*.h -lreadline -lhistory -L$(RL_LIB) -I$(RL_INC) $(SRCS_TEST) ./testFile/libft/*.c -g

clean :
	@$(RM) $(OBJ_DIR)
	@echo "🗑 Remove $(NAME)'s OBJs Done"

fclean : clean
	@$(RM) $(NAME)
	@echo "🗑 Remove $(NAME) Done"

wclean : fclean $(LIBFT_NAME)_fclean

re: fclean all

rr : wclean all

.PHONY : all clean fclean wclean re rr \
	$(LIBFT_NAME)_clean $(LIBFT_NAME)_fclean

$(LIBFT) :
	@make -C $(LIBFT_DIR)

$(LIBFT_NAME)_clean :
	@make -C $(LIBFT_DIR) clean

$(LIBFT_NAME)_fclean :
	@make -C $(LIBFT_DIR) fclean
