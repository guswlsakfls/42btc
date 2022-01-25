/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/25 21:35:00 by hyujo            ###   ########.fr       */
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
	int		size;
}	t_deq;

void	ft_a_to_b(t_deq *a, t_deq *b, int size);
void	ft_b_to_a(t_deq *a, t_deq *b, int size);

t_deq	*ft_init_deq(void)
{
	t_deq	*deq;

	deq = malloc(sizeof(t_deq));
	if (!deq)
		return (NULL);
	deq->top = NULL;
	deq->bottom = NULL;
	deq->size = 0;
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
	ft_swap(a->top, a->top->next);
	ft_putstr_fd("sa\n", 1);
}

void	ft_sb(t_deq *b)
{
	ft_swap(b->top, b->top->next);
	ft_putstr_fd("sb\n", 1);
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

	b->size++;
	tmp = ft_pop_front(a);
	ft_push_front(b, tmp);
	ft_putstr_fd("pb\n", 1);
}

void	ft_pa(t_deq *a, t_deq *b)
{
	t_node	*tmp;

	a->size++;
	tmp = ft_pop_front(b);
	ft_push_front(a, tmp);
	ft_putstr_fd("pa\n", 1);
}

void	ft_ra(t_deq *a)
{
	t_node	*tmp;

	a->size++;
	tmp = ft_pop_front(a);
	ft_push_back(a, tmp);
	ft_putstr_fd("ra\n", 1);
}

void	ft_rb(t_deq *b)
{
	t_node	*tmp;

	b->size++;
	tmp = ft_pop_front(b);
	ft_push_back(b, tmp);
	ft_putstr_fd("rb\n", 1);
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

	tmp = ft_pop_back(a);
	ft_push_front(a, tmp);
	ft_putstr_fd("rra\n", 1);
}

void	ft_rrb(t_deq *b)
{
	t_node	*tmp;

	tmp = ft_pop_back(b);
	ft_push_front(b, tmp);
	ft_putstr_fd("rrb\n", 1);
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

int	ft_size_deq(t_deq *deq)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = deq->top;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_a_to_b(t_deq *a, t_deq *b, int size)
{
	int	pivot;
	int	rra;

	if (size <= 1)
		return ;
	pivot = a->bottom->data;
	a->size = 0;
	b->size = 0;
	while (--size > 0)
	{
		if (a->top->data > pivot)
			ft_ra(a);
		else
			ft_pb(a, b);
	}
	rra = a->size;
	while (--rra >= 0)
		ft_rra(a);
	ft_a_to_b(a, b, a->size + 1);
	ft_b_to_a(a, b, b->size + 1);
}

void	ft_b_to_a(t_deq *a, t_deq *b, int size)
{
	int	pivot;
	int	rrb;

	if (size <= 1)
		return ;
	pivot = b->bottom->data;
	a->size = 0;
	b->size = 0;
	while (--size > 0)
	{
		if (b->top->data > pivot)
			ft_rb(b);
		else
			ft_pa(a, b);
	}
	rrb = b->size;
	while (--rrb >= 0)
		ft_rrb(b);
	ft_a_to_b(a, b, a->size + 1);
	ft_b_to_a(a, b, b->size + 1);
}

int	main(int argc, char **argv)
{
	t_node	*node;
	t_deq	*a;
	t_deq	*b;
	int		data;
	int		i;
	int		size;

	if (argc <= 2) // 인자가 아무것도 안들어오고, 하나만 들어 왔을 때 예외처리
		return (0);

	// ft_ceate_deq(a, b)
	a = ft_init_deq();
	b = ft_init_deq();
	i = 1;
	data = 0;
	while (i < argc)
	{
		data = ft_atoi(argv[i]);
		node = ft_init_node(data);
		ft_push_back(a, node);
		i++;
	}

	// 연습___________________________
	size = ft_size_deq(a);
	ft_a_to_b(a, b, size);


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
	printf("-\nb\n");
	return (0);
}
