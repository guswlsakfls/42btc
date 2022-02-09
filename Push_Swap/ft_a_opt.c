/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_a_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:34:53 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 16:12:27 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

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

void	ft_ex_sort_a_five(t_deq *a, t_deq *b)
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

void	ft_sort_a_three(t_deq *a)
{
	if (a->top->data > a->top->next->data
		&& a->top->data > a->top->next->next->data)
	{
		ft_sa(a);
		ft_ra(a);
		ft_sa(a);
		ft_rra(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->data > a->top->data
		&& a->top->next->data > a->top->next->next->data)
	{
		ft_ra(a);
		ft_sa(a);
		ft_rra(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->next->data > a->top->data
		&& a->top->next->next->data > a->top->next->data)
	{
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
}

void	ft_ex_sort_a_three(t_deq *a)
{
	if (a->top->data > a->top->next->data
		&& a->top->data > a->top->next->next->data)
	{
		ft_ra(a);
		ft_sa(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->data > a->top->data
		&& a->top->next->data > a->top->next->next->data)
	{
		ft_rra(a);
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
	if (a->top->next->next->data > a->top->data
		&& a->top->next->next->data > a->top->next->data)
	{
		if (a->top->data > a->top->next->data)
			ft_sa(a);
		return ;
	}
}
