/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 01:19:03 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

void	ft_print_Error(void)
{
	write(1, "Error\n", 6);
}

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

void	ft_a_to_b(t_deq *a, t_deq *b, int size);
void	ft_b_to_a(t_deq *a, t_deq *b, int size);
int	*ft_stack_to_arr(t_deq *deq, int size);

t_deq	*ft_init_deq(void)
{
	t_deq	*deq;
	int		i;

	deq = malloc(sizeof(t_deq));
	if (!deq)
		return (NULL);
	deq->top = NULL;
	deq->bottom = NULL;
	deq->size = 0;
	deq->flag = 0;
	i = 0;
	while (i <= 1000)
	{
		deq->arr[i] = 0;
		i++;
	}
	return (deq);
}

t_node	*ft_init_node(int data)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = data;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	ft_push_back(t_deq *deq, t_node *new_node)
{
	if (!deq->bottom)
	{
		deq->top = new_node;
		deq->bottom = new_node;
	}
	else
	{
		new_node->prev = deq->bottom;
		deq->bottom->next = new_node;
		deq->bottom = new_node;
	}
}

void	ft_push_front(t_deq *deq, t_node *new_node)
{
	if (!deq->top)
	{
		deq->top = new_node;
		deq->bottom = new_node;
	}
	else
	{
		new_node->next = deq->top;
		deq->top->prev = new_node;
		deq->top = new_node;
	}
}

t_node	*ft_pop_front(t_deq *deq)
{
	t_node	*tmp;

	tmp = deq->top;
	if (!deq->top->next) // 노드가 하나만 들어왔을 때 bottom 주소가 남아 있다.
		deq->bottom = NULL;
	deq->top = deq->top->next;
	if (deq->top) // 스택에 하나의 노드값만 있게되면 top = NULL 이 되서 접근할 수 없다.
		deq->top->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_node	*ft_pop_back(t_deq *deq)
{
	t_node	*tmp;

	tmp = deq->bottom;
	if (!deq->top->next) // 노드가 하나만 들어왔을 때
		deq->top = NULL;
	deq->bottom = deq->bottom->prev;
	if (deq->bottom)
		deq->bottom->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	ft_swap(t_node *a, t_node *b)
{
	int	tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

void	ft_sa(t_deq *a)
{
	if (a->top->next) // if 문 준 이유는 하나만 들어 왔을때가 있기 때문에 그대로 내보내 주려고
	{
		ft_swap(a->top, a->top->next);
		ft_putstr_fd("sa\n", 1);
	}
}

void	ft_sb(t_deq *b)
{
	if (b->top->next)
	{
		ft_swap(b->top, b->top->next);
		ft_putstr_fd("sb\n", 1);
	}
}

void	ft_ss(t_deq *a, t_deq *b)
{
	ft_swap(a->top, a->top->next);
	ft_swap(b->top, b->top->next);
	ft_putstr_fd("ss\n", 1);
}

void	ft_pb(t_deq *a, t_deq *b)
{
	t_node	*tmp;

	if (a->top)
	{
		tmp = ft_pop_front(a);
		ft_push_front(b, tmp);
		ft_putstr_fd("pb\n", 1);
	}
}

void	ft_pa(t_deq *a, t_deq *b)
{
	t_node	*tmp;

	if (b->top)
	{
		tmp = ft_pop_front(b);
		ft_push_front(a, tmp);
		ft_putstr_fd("pa\n", 1);
	}
}

void	ft_ra(t_deq *a)
{
	t_node	*tmp;

	if (a->top->next)
	{
		tmp = ft_pop_front(a);
		ft_push_back(a, tmp);
		ft_putstr_fd("ra\n", 1);
	}
}

void	ft_rb(t_deq *b)
{
	t_node	*tmp;

	if (b->top->next)
	{
		tmp = ft_pop_front(b);
		ft_push_back(b, tmp);
		ft_putstr_fd("rb\n", 1);
	}
}

void	ft_rr(t_deq *a, t_deq *b)
{
	t_node	*tmp;

	tmp = ft_pop_front(a);
	ft_push_back(a, tmp);
	tmp = ft_pop_front(b);
	ft_push_back(b, tmp);
	ft_putstr_fd("rr\n", 1);
}

void	ft_rra(t_deq *a)
{
	t_node	*tmp;

	if (a->top->next)
	{
		tmp = ft_pop_back(a);
		ft_push_front(a, tmp);
		ft_putstr_fd("rra\n", 1);
	}
}

void	ft_rrb(t_deq *b)
{
	t_node	*tmp;

	if (b->top->next)
	{
		tmp = ft_pop_back(b);
		ft_push_front(b, tmp);
		ft_putstr_fd("rrb\n", 1);
	}
}

void	ft_rrr(t_deq *a, t_deq *b)
{
	t_node	*tmp;

	tmp = ft_pop_back(a);
	ft_push_front(a, tmp);
	tmp = ft_pop_back(b);
	ft_push_front(b, tmp);
	ft_putstr_fd("rrr\n", 1);
}

void	ft_sort_b_two(t_deq *a, t_deq *b)
{
	if (b->top->data < b->top->next->data)
		ft_sb(b);
	ft_pa(a, b);
	ft_pa(a, b);
}

void ft_sort_a_three(t_deq *a)
{
	if (a->top->data > a->top->next->data && a->top->data > a->top->next->next->data)
	{
		ft_sa(a);
		ft_ra(a);
		ft_sa(a);
		ft_rra(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->data > a->top->data && a->top->next->data > a->top->next->next->data)
	{
		ft_ra(a);
		ft_sa(a);
		ft_rra(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->next->data > a->top->data && a->top->next->next->data > a->top->next->data)
	{
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
}

void ft_ex_sort_a_three(t_deq *a)
{
	if (a->top->data > a->top->next->data && a->top->data > a->top->next->next->data)
	{
		ft_ra(a);
		ft_sa(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->data > a->top->data && a->top->next->data > a->top->next->next->data)
	{
		ft_rra(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->next->data > a->top->data && a->top->next->next->data > a->top->next->data)
	{
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
}

int	ft_sort_arr(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;
	int	flag;

	flag = 0;
	i = 0;
	tmp = 0;
	while (++i < size)
	{
		j = -1;
		while (++j < size - i)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = 1;
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	if (flag == 0)
		return (0);
	return (1);
}

void ft_ex_sort_a_five(t_deq *a, t_deq *b)
{
	t_node	*node;
	int		*arr;
	int		i;

	arr = malloc(sizeof(int) * 5);
	if (!arr)
		return ;
	node = a->top;
	i = -1;
	while (++i < 5)
	{
		arr[i] = node->data;
		node = node->next;
	}
	ft_sort_arr(arr, 5);
	i = -1;
	while (++i < 5)
	{
		if (arr[2] > a->top->data)
			ft_pb(a, b);
		else
			ft_ra(a);
	}
	free(arr);
	ft_ex_sort_a_three(a);
	ft_sort_b_two(a, b);
}

void	ft_sort_a_under_four(t_deq *a, int size)
{
	if (size <= 1)
		return ;
	if (size == 2)
	{
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (size == 3)
		ft_sort_a_three(a);
}

void	ft_sort_b_under_six(t_deq *a, t_deq *b, int size)
{
	if (size <= 1)
	{
		ft_pa(a, b);
		return ;
	}
	if (size == 2)
	{
		ft_sort_b_two(a, b);
		return ;
	}
	if (size == 3)
	{
		if (b->top->next->data > b->top->data && b->top->next->data > b->top->next->next->data)
			ft_sb(b);
		if (b->top->data > b->top->next->data && b->top->data > b->top->next->next->data)
		{
			ft_pa(a, b);
			ft_sort_b_two(a, b);
		}
		else
		{
			ft_rb(b);
			ft_sb(b);
			ft_pa(a, b);
			ft_rrb(b);
			ft_sort_b_two(a, b);
		}
	}
	// if (size == 5)
	// 	ft_sort_b_five(a, b);
}

int	ft_get_pivot(t_deq *deq, int size)
{
	int	*arr;
	int	pivot;

	arr = ft_stack_to_arr(deq, size);
	ft_sort_arr(arr, size);
	pivot = arr[size / 2];
	free(arr);
	return (pivot);
}

void	ft_a_to_b(t_deq *a, t_deq *b, int size)
{
	int	pivot;
	int	rra;
	int	i;
	int	a_size;   // 구조체로 데리고 다니면 전역변수가 되서 스택을 이용할때 값이 꼬인다.
	int	b_size;

	if (size < 4)
	{
		ft_sort_a_under_four(a, size);
		return ;
	}
	pivot = ft_get_pivot(a, size);
	a_size = 0;
	b_size = 0;
	i = -1;
	while (++i < size)
	{
		if (a->top->data > pivot)
		{
			ft_ra(a);
			a_size++;
		}
		else
		{
			ft_pb(a, b);
			b_size++;
		}
	}
	rra = a_size;
	while (--rra >= 0 && a->top->next && a->flag == 1) // 노드가 2개 이상일때만 이거는 나중에 초기 예외처리에서 제외될듯
		ft_rra(a);
	ft_a_to_b(a, b, a_size);
	ft_b_to_a(a, b, b_size);
}

void	ft_b_to_a(t_deq *a, t_deq *b, int size)
{
	int	pivot;
	int	rrb;
	int	i;
	int	a_size;   // 구조체로 데리고 다니면 전역변수가 되서 스택을 이용할때 값이 꼬인다.
	int	b_size;

	a->flag = 1;
	if (size <= 3)
	{
		ft_sort_b_under_six(a, b, size);
		return ;
	}
	pivot = ft_get_pivot(b, size);
	a_size = 0;
	b_size = 0;
	i = -1;
	while (++i < size)
	{
		if (b->top->data < pivot)
		{
			ft_rb(b);
			b_size++;
		}
		else
		{
			ft_pa(a, b);
			a_size++;
		}
	}
	rrb = b_size;
	while (--rrb >= 0 && b->top->next)
		ft_rrb(b);
	ft_a_to_b(a, b, a_size);
	ft_b_to_a(a, b, b_size);
}

void	ft_check_dup(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				exit(0);
			j++;
		}
		i++;
	}
}

int	ft_check_not_digit(char **arr, int i, int j)
{
	if (arr[i][j] != ' ' && arr[i][j] != '+' && arr[i][j] != '-')
		return (1);
	if (arr[i][j] == '-' && !ft_isdigit(arr[i][j + 1]))
		return (1);
	if (arr[i][j] == '+' && !ft_isdigit(arr[i][j + 1]))
		return (1);
	return (0);
}

void	ft_get_stack_a(int ac, char **av, t_deq *a)
{
	int			i;
	int			j;
	char		**arr;
	long long	num;
	t_node		*node;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]) && ft_check_not_digit(av, i, j))
			{
				ft_print_Error();
				exit(0);
			}
		}
		arr = ft_split(av[i], ' ');
		j = -1;
		while (arr[++j])
		{
			num = ft_atoi(arr[j]);
			if (-2147483648 > num || num > 2147483647)
			{
				ft_print_Error();
				exit(0);
			}
			node = ft_init_node(num);
			a->size++;
			ft_push_back(a, node);
		}
		j = -1;
		while (arr[++j])
			free(arr[j]);
		free(arr);
	}
}

int	*ft_stack_to_arr(t_deq *deq, int size)
{
	int		*arr;
	t_node	*node;
	int		i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	node = deq->top;
	while (i < size)
	{
		arr[i] = node->data;
		node = node->next;
		i++;
	}
	return (arr);
}

int	main(int argc, char **argv)
{
	t_node	*node;
	t_deq	*a;
	t_deq	*b;
	int		*arr;

	if (argc <= 2) // 인자가 아무것도 안들어오고, 하나만 들어 왔을 때 예외처리
	{
		ft_print_Error();
		return (0);
	}
	a = ft_init_deq();
	b = ft_init_deq();
	ft_get_stack_a(argc, argv, a);
	arr = ft_stack_to_arr(a, a->size);
	if (!ft_sort_arr(arr, a->size))
		exit(0);
	ft_check_dup(arr, a->size);
	free(arr);
	if (a->size == 3)
	{
		ft_ex_sort_a_three(a);
		return (0);
	}
	if (a->size == 5)
	{
		ft_ex_sort_a_five(a, b);
		return (0);
	}
	// 연습___________________________
	ft_a_to_b(a, b, a->size);
	// test__________________________
	
	// ft_push_swap 부분
	// while (a->top)
	// {
	// 	printf("%d\n", a->top->data);
	// 	a->top = a->top->next;
	// }

	// printf("-\na\n\n");
	// while (b->top)
	// {
	// 	printf("%d\n", b->top->data);
	// 	b->top = b->top->next;
	// }
	// printf("-\nb\n\n\n");


	while (a->top)
	{
		node = ft_pop_front(a);
		free(node);
	}
	free(a);
	free(b);
	return (0);
}
