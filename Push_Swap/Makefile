NAME = push_swap.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar -rcs
RM = rm -f

LIB_DIR = ./libft

SRCS = push_swap.c \
		ft_a_opt.c \
		ft_b_opt.c \
		ft_arr.c \
		ft_ab_to.c \
		ft_commands_1.c \
		ft_commands_2.c \
		ft_commands_3.c \
		ft_deq.c \
		ft_init.c \
		ft_utils.c \
		ft_get_stack_a.c

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o) -I. -I$(LIB_DIR)

$(NAME): $(OBJS)
	$(MAKE) all -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $@ $^
	$(CC) $@ -o push_swap

all: $(NAME)

bonus : all

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
