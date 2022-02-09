/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ab_to.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:58:10 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 15:05:09 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_a_to_b(t_deq *a, t_deq *b, int size)
{
	int	pivot;
	int	rra;
	int	i;
	int	a_size;
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
	while (--rra >= 0 && a->top->next && a->flag == 1)
		ft_rra(a);
	ft_a_to_b(a, b, a_size);
	ft_b_to_a(a, b, b_size);
}

void	ft_b_to_a(t_deq *a, t_deq *b, int size)
{
	int	pivot;
	int	rrb;
	int	i;
	int	a_size;
	int	b_size;

	a->flag = 1;
	if (size <= 3)
	{
		ft_sort_b_under_four(a, b, size);
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
	while (--rrb >= 0 && b->top->next && ft_skip_rrb(b, b_size))
		ft_rrb(b);
	ft_a_to_b(a, b, a_size);
	ft_b_to_a(a, b, b_size);
}
