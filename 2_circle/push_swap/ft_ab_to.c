/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ab_to.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:58:10 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 17:31:27 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_divide_a(t_deq *a, t_deq *b, int *a_size, int *b_size)
{
	int	i;
	int	pivot;

	pivot = ft_get_pivot(a, a->size);
	i = -1;
	while (++i < a->size)
	{
		if (a->top->data > pivot)
		{
			ft_ra(a);
			(*a_size)++;
		}
		else
		{
			ft_pb(a, b);
			(*b_size)++;
		}
	}
}

void	ft_a_to_b(t_deq *a, t_deq *b, int size)
{
	int	rra;
	int	a_size;
	int	b_size;

	if (size < 4)
	{
		ft_sort_a_under_four(a, size);
		return ;
	}
	a_size = 0;
	b_size = 0;
	a->size = size;
	ft_divide_a(a, b, &a_size, &b_size);
	rra = a_size;
	while (--rra >= 0 && a->top->next && a->flag == 1)
		ft_rra(a);
	ft_a_to_b(a, b, a_size);
	ft_b_to_a(a, b, b_size);
}

void	ft_divide_b(t_deq *a, t_deq *b, int *a_size, int *b_size)
{
	int	i;
	int	pivot;

	pivot = ft_get_pivot(b, b->size);
	i = -1;
	while (++i < b->size)
	{
		if (b->top->data < pivot)
		{
			ft_rb(b);
			(*b_size)++;
		}
		else
		{
			ft_pa(a, b);
			(*a_size)++;
		}
	}
}

void	ft_b_to_a(t_deq *a, t_deq *b, int size)
{
	int	rrb;
	int	a_size;
	int	b_size;

	a->flag = 1;
	if (size <= 3)
	{
		ft_sort_b_under_four(a, b, size);
		return ;
	}
	a_size = 0;
	b_size = 0;
	b->size = size;
	ft_divide_b(a, b, &a_size, &b_size);
	rrb = b_size;
	while (--rrb >= 0 && b->top->next && ft_skip_rrb(b, b_size))
		ft_rrb(b);
	ft_a_to_b(a, b, a_size);
	ft_b_to_a(a, b, b_size);
}
