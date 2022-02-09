/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_stack_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:00:39 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 16:00:46 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_check_arg(int i, int j, char **av)
{
	if (!ft_isdigit(av[i][j]) && ft_check_not_digit(av, i, j))
	{
		ft_print_error();
		exit(0);
	}
}

void	ft_check_integer(long long num)
{
	if (-2147483648 > num || num > 2147483647)
	{
		ft_print_error();
		exit(0);
	}
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
}

void	ft_get_stack_a(int ac, char **av, t_deq *a)
{
	int			i;
	int			j;
	char		**arr;
	long long	num;
	t_node		*node;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			ft_check_arg(i, j, av);
		arr = ft_split(av[i], ' ');
		j = -1;
		while (arr[++j])
		{
			num = ft_atoi(arr[j]);
			ft_check_integer(num);
			node = ft_init_node(num);
			a->size++;
			ft_push_back(a, node);
		}
		ft_free_arr(arr);
		free(arr);
	}
}
