/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:32:08 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 14:32:13 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_swap(t_node *a, t_node *b)
{
	int	tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

void	ft_sa(t_deq *a)
{
	if (a->top->next)
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
