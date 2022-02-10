/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_b_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:36:45 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 18:29:20 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_sort_a_two(t_deq *a)
{
	if (a->top->data > a->top->next->data)
		ft_sa(a);
}

void	ft_sort_b_two(t_deq *a, t_deq *b)
{
	if (b->top->data < b->top->next->data)
		ft_sb(b);
	ft_pa(a, b);
	ft_pa(a, b);
}

void	ft_sort_b_three(t_deq *a, t_deq *b)
{
	if (b->top->next->data > b->top->data
		&& b->top->next->data > b->top->next->next->data)
		ft_sb(b);
	if (b->top->data > b->top->next->data
		&& b->top->data > b->top->next->next->data)
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

void	ft_sort_b_under_four(t_deq *a, t_deq *b, int size)
{
	if (size <= 1)
		ft_pa(a, b);
	else if (size == 2)
		ft_sort_b_two(a, b);
	else if (size == 3)
		ft_sort_b_three(a, b);
}
