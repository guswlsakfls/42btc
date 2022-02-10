/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:52:50 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/10 11:40:34 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_check_not_digit(char **arr, int i, int j)
{
	if (arr[i][j] != ' ' && arr[i][j] != '+' && arr[i][j] != '-')
		return (1);
	if (arr[i][j] == '-' && !ft_isdigit(arr[i][j + 1]))
		return (1);
	if (arr[i][j] == '+' && !ft_isdigit(arr[i][j + 1]))
		return (1);
	return (0);
}

int	ft_get_pivot(t_deq *deq, int size)
{
	int	*arr;
	int	pivot;

	arr = ft_stack_to_arr(deq, size);
	ft_sort_arr(arr, size);
	pivot = arr[size / 2];
	free(arr);
	return (pivot);
}

void	ft_check_dup(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
			{
				ft_print_error();
				exit(0);
			}
			j++;
		}
		i++;
	}
}

int	ft_skip_rrb(t_deq *b, int size)
{
	t_node	*node;
	int		i;

	i = 0;
	node = b->top;
	while (node)
	{
		node = node->next;
		i++;
	}
	if (size == i)
		return (0);
	return (1);
}

void	ft_print_error(void)
{
	write(1, "Error\n", 6);
}
