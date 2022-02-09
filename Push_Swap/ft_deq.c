/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deq_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:29:58 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 14:31:56 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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
	if (!deq->top->next)
		deq->bottom = NULL;
	deq->top = deq->top->next;
	if (deq->top)
		deq->top->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_node	*ft_pop_back(t_deq *deq)
{
	t_node	*tmp;

	tmp = deq->bottom;
	if (!deq->top->next)
		deq->top = NULL;
	deq->bottom = deq->bottom->prev;
	if (deq->bottom)
		deq->bottom->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}
