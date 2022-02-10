/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:33:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 14:33:19 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_pa(t_deq *a, t_deq *b)
{
	t_node	*tmp;

	if (b->top)
	{
		tmp = ft_pop_front(b);
		ft_push_front(a, tmp);
		ft_putstr_fd("pa\n", 1);
	}
}

void	ft_ra(t_deq *a)
{
	t_node	*tmp;

	if (a->top->next)
	{
		tmp = ft_pop_front(a);
		ft_push_back(a, tmp);
		ft_putstr_fd("ra\n", 1);
	}
}

void	ft_rb(t_deq *b)
{
	t_node	*tmp;

	if (b->top->next)
	{
		tmp = ft_pop_front(b);
		ft_push_back(b, tmp);
		ft_putstr_fd("rb\n", 1);
	}
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

	if (a->top->next)
	{
		tmp = ft_pop_back(a);
		ft_push_front(a, tmp);
		ft_putstr_fd("rra\n", 1);
	}
}
