/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:28:55 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 15:47:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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
