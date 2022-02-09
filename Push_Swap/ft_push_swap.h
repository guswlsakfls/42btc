/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:16:20 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 15:47:10 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdlib.h>

typedef struct s_node
{
	int				data;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_deq
{
	t_node	*top;
	t_node	*bottom;
	int		arr[1000];
	int		size;
	int		flag;
}	t_deq;

void	ft_print_error(void);
t_deq	*ft_init_deq(void);
t_node	*ft_init_node(int data);
void	ft_push_back(t_deq *deq, t_node *new_node);
void	ft_push_front(t_deq *deq, t_node *new_node);
t_node	*ft_pop_front(t_deq *deq);
t_node	*ft_pop_back(t_deq *deq);
void	ft_swap(t_node *a, t_node *b);
void	ft_sa(t_deq *a);
void	ft_sb(t_deq *b);
void	ft_ss(t_deq *a, t_deq *b);
void	ft_pb(t_deq *a, t_deq *b);
void	ft_pa(t_deq *a, t_deq *b);
void	ft_ra(t_deq *a);
void	ft_rb(t_deq *b);
void	ft_rr(t_deq *a, t_deq *b);
void	ft_rra(t_deq *a);
void	ft_rrb(t_deq *b);
void	ft_rrr(t_deq *a, t_deq *b);
void	ft_sort_b_two(t_deq *a, t_deq *b);
void	ft_sort_a_three(t_deq *a);
void	ft_ex_sort_a_three(t_deq *a);
int		ft_sort_arr(int *arr, int size);
void	ft_ex_sort_a_five(t_deq *a, t_deq *b);
void	ft_sort_a_under_four(t_deq *a, int size);
void	ft_sort_b_under_four(t_deq *a, t_deq *b, int size);
int		ft_get_pivot(t_deq *deq, int size);
void	ft_a_to_b(t_deq *a, t_deq *b, int size);
int		ft_skip_rrb(t_deq *b, int size);
void	ft_b_to_a(t_deq *a, t_deq *b, int size);
void	ft_check_dup(int *arr, int size);
int		ft_check_not_digit(char **arr, int i, int j);
void	ft_get_stack_a(int ac, char **av, t_deq *a);
int		*ft_stack_to_arr(t_deq *deq, int size);
void	ft_arg(int argc, char **argv, t_deq *a);
void	ft_free(t_deq *a, t_deq *b);
void	ft_check_arg(int i, int j, char **av);
void	ft_check_integer(long long num);
void	ft_free_arr(char **arr);

#endif
