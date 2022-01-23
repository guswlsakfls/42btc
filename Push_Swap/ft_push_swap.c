/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/23 17:15:39 by hyujo            ###   ########.fr       */
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
	if (!deq->top)
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
	deq->top->next->prev = NULL;
	return (tmp);
}

t_node	*ft_pop_back(t_deq *deq)
{
	t_node	*tmp;

	tmp = deq->bottom;
	deq->bottom = deq->bottom->prev;
	deq->bottom->next = NULL;
	return (tmp);
}

int	main(int argc, char **argv)
{
	t_node	*node;
	t_deq	*deq;
	t_node	*pivot;
	int		data;
	int		i;

	if (argc <= 2) // 인자가 아무것도 안들어오고, 하나만 들어 왔을 때 예외처리
		return (0);

	// ft_ceate_deq
	deq = ft_init_deq();
	i = 1;
	data = 0;
	while (i < argc)
	{
		data = ft_atoi(argv[i]);
		node = ft_init_node(data);
		ft_push_back(deq, node);
		i++;
	}
	deq->size = i;
	// ft_push_swap 부분
	pivot = deq->top;
	printf("pivot : %d\n", deq->size / 2);
	while (i < deq->size / 2)
		pivot = pivot->next;
	while (deq->top)
	{
		printf("%d\n", deq->top->data);
		deq->top = deq->top->next;
	}
	return (0);
}
