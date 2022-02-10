/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_a_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:34:53 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 18:34:00 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_sort_a_under_four(t_deq *a, int size)
{
	if (size == 2)
		ft_sort_a_two(a);
	else if (size == 3)
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
	while (++i < 11)
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

int	ft_check_three(t_deq *a)
{
	if (a->top->data > a->top->next->data
		&& a->top->data > a->top->next->next->data)
		return (1);
	else if (a->top->next->data > a->top->data
		&& a->top->next->data > a->top->next->next->data)
		return (2);
	else if (a->top->next->next->data > a->top->data
		&& a->top->next->next->data > a->top->next->data)
		return (3);
	return (0);
}

void	ft_sort_a_three(t_deq *a)
{
	if (ft_check_three(a) == 1)
	{
		ft_sa(a);
		ft_ra(a);
		ft_sa(a);
		ft_rra(a);
		ft_sort_a_two(a);
	}
	else if (ft_check_three(a) == 2)
	{
		ft_ra(a);
		ft_sa(a);
		ft_rra(a);
		ft_sort_a_two(a);
	}
	else if (ft_check_three(a) == 3)
		ft_sort_a_two(a);
}

void	ft_ex_sort_a_three(t_deq *a)
{
	if (ft_check_three(a) == 1)
	{
		ft_ra(a);
		ft_sa(a);
		ft_sort_a_two(a);
	}
	if (ft_check_three(a) == 2)
	{
		ft_rra(a);
		ft_sort_a_two(a);
	}
	if (ft_check_three(a) == 3)
		ft_sort_a_two(a);
}
