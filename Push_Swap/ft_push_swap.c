/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/04 22:35:49 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

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
}	t_deq;

void	ft_a_to_b(t_deq *a, t_deq *b, int size);
void	ft_b_to_a(t_deq *a, t_deq *b, int size);

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

void	ft_sort_a_under_three(t_deq *deq, int size)
{
	if (size <= 1)
		return ;
	if (size == 2)
	{
		if (deq->top->data > deq->top->next->data)
			ft_sa(deq);
		return ;
	}
	if (size == 3)
	{
		if (deq->top->data > deq->top->next->data && deq->top->data > deq->top->next->next->data)
		{
			ft_sa(deq);
			ft_ra(deq);
			ft_sa(deq);
			ft_rra(deq);
			if (deq->top->data > deq->top->next->data)
				ft_sa(deq);
			return ;
		}
		if (deq->top->next->data > deq->top->data && deq->top->next->data > deq->top->next->next->data)
		{
			ft_ra(deq);
			ft_sa(deq);
			ft_rra(deq);
			if (deq->top->data > deq->top->next->data)
				ft_sa(deq);
			return ;
		}
		if (deq->top->next->next->data > deq->top->data && deq->top->next->next->data > deq->top->next->data)
		{
			if (deq->top->data > deq->top->next->data)
				ft_sa(deq);
			return ;
		}
	}
	if (size == 5)
	{
		if (a->top->data > a->top->next->data && a->top->data > a->top->next->next->data && a->top->data > a->top->next->next->next->data)
		{

		}
	}
}

void	ft_sort_b_under_two(t_deq *a, t_deq *b)
{
	if (b->top->data < b->top->next->data)
		ft_sb(b);
	ft_pa(a, b);
	ft_pa(a, b);
}

void	ft_sort_b_under_three(t_deq *a, t_deq *b, int size)
{
	if (size <= 1)
	{
		ft_pa(a, b);
		return ;
	}
	if (size == 2)
	{
		ft_sort_b_under_two(a, b);
		return ;
	}
	if (b->top->next->data > b->top->data && b->top->next->data > b->top->next->next->data)
		ft_sb(b);
	if (b->top->data > b->top->next->data && b->top->data > b->top->next->next->data)
	{
		ft_pa(a, b);
		ft_sort_b_under_two(a, b);
	}
	else
	{
		ft_rb(b);
		ft_sb(b);
		ft_pa(a, b);
		ft_rrb(b);
		ft_sort_b_under_two(a, b);
	}
}

// int	ft_get_pivot(t_deq *a, int size)

void	ft_a_to_b(t_deq *a, t_deq *b, int size)
{
	int	pivot;
	int	rra;
	int	i;
	int	a_size;   // 구조체로 데리고 다니면 전역변수가 되서 스택을 이용할때 값이 꼬인다.
	int	b_size;

	if (size <= 3)
	{
		ft_sort_a_under_three(a, size);
		return ;
	}
	pivot = a->arr[a->size - (size / 2)];
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
	while (--rra >= 0 && a->top->next) // 노드가 2개 이상일때만 이거는 나중에 초기 예외처리에서 제외될듯
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

	if (size <= 3)
	{
		ft_sort_b_under_three(a, b, size);
		return ;
	}
	pivot = b->arr[size / 2];
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

void	ft_sort_arr(t_deq *a, t_deq *b)
{
	int	i;
	int	j;
	int	tmp;
	int	flag;

	flag = 0;
	i = -1;
	tmp = 0;
	while (++i < a->size)
	{
		j = 0;
		while (j < a->size - i)
		{
			if (a->arr[j] > a->arr[j + 1])
			{
				flag = 1;
				tmp = a->arr[j];
				a->arr[j] = a->arr[j + 1];
				a->arr[j + 1] = tmp;
			}
			j++;
		}
	}
	if (flag == 0)
		exit(0);
	i = -1;
	while (a->arr[++i])
		b->arr[i] = a->arr[i];
	b->arr[i] = '\0';
}

void	ft_check_dup(t_deq *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->size)
	{
		j = i + 1;
		while (j < a->size + 1)
		{
			if (a->arr[i] == a->arr[j])
				exit(0);
			j++;
		}
		i++;
	}
}

void	ft_get_arr(int ac, char **av, t_deq *a, t_deq *b)
{
	int			i;
	int			j;
	int			k;
	char		**arr;
	long long	num;

	i = 0;
	k = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]) && av[i][j] != ' ' && av[i][j] != '-')
			{
				ft_putstr_fd("Error", 1);
				exit(0);
			}
		}
		arr = ft_split(av[i], ' ');
		j = -1;
		while (arr[++j])
		{
			num = ft_atoi(arr[j]);
			if (-2147483648 > num || num > 2147483647)
				exit(0);
			a->arr[k++] = num;
			if (k == 1001)
				exit(0);
		}
		j = -1;
		while (arr[++j])
			free(arr[j]);
		free(arr);
	}
	a->size = k - 1; // 인덱스 0부터니까 하나 뺌
	b->size = k - 1;
	a->arr[k] = '\0';
}

int	main(int argc, char **argv)
{
	t_node	*node;
	t_node	*tmp;
	t_deq	*a;
	t_deq	*b;
	int		i;

	if (argc <= 2) // 인자가 아무것도 안들어오고, 하나만 들어 왔을 때 예외처리
		return (0);
	a = ft_init_deq();
	b = ft_init_deq();
	ft_get_arr(argc, argv, a, b);
	i = -1;
	while (++i < a->size + 1) // data 값이 0 이면 탈출해 버리는 거 같다. a->arr[++i] 이거 교체.
	{
		node = ft_init_node(a->arr[i]);
		ft_push_back(a, node);
	}
	ft_sort_arr(a, b);
	ft_check_dup(a);
	// 연습___________________________
	ft_a_to_b(a, b, a->size + 1);
	// test__________________________
	
	// ft_push_swap 부분
	while (a->top)
	{
		printf("%d\n", a->top->data);
		a->top = a->top->next;
	}

	printf("-\na\n\n");
	while (b->top)
	{
		printf("%d\n", b->top->data);
		b->top = b->top->next;
	}
	printf("-\nb\n\n\n");
	while (a->top)
	{
		tmp = ft_pop_front(a);
		free(tmp);
	}
	free(a);
	free(b);
	return (0);
}
