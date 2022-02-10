/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:33:32 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 14:33:33 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_rrb(t_deq *b)
{
	t_node	*tmp;

	if (b->top->next)
	{
		tmp = ft_pop_back(b);
		ft_push_front(b, tmp);
		ft_putstr_fd("rrb\n", 1);
	}
}

void	ft_rrr(t_deq *a, t_deq *b)
{
	t_node	*tmp;

	tmp = ft_pop_back(a);
	ft_push_front(a, tmp);
	tmp = ft_pop_back(b);
	ft_push_front(b, tmp);
	ft_putstr_fd("rrr\n", 1);
}
