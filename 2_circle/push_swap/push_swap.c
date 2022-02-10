/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/10 18:20:41 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_arg(int argc, char **argv, t_deq *a)
{
	int	*arr;

	ft_get_stack_a(argc, argv, a);
	if (a->size < 2)
	{
		ft_print_error();
		exit(1);
	}
	arr = ft_stack_to_arr(a, a->size);
	ft_check_dup(arr, a->size);
	if (!ft_sort_arr(arr, a->size))
		exit(0);
	free(arr);
}

void	ft_free(t_deq *a, t_deq *b)
{
	t_node	*node;

	while (a->top)
	{
		node = ft_pop_front(a);
		free(node);
	}
	free(a);
	free(b);
}

int	main(int argc, char **argv)
{
	t_deq	*a;
	t_deq	*b;

	if (argc <= 2)
		return (0);
	a = ft_init_deq();
	b = ft_init_deq();
	ft_arg(argc, argv, a);
	if (a->size == 3)
	{
		ft_ex_sort_a_three(a);
		return (0);
	}
	else if (a->size == 5)
	{
		ft_ex_sort_a_five(a, b);
		return (0);
	}
	else
		ft_a_to_b(a, b, a->size);
	ft_free(a, b);
	return (0);
}
