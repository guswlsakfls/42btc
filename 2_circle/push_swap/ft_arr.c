/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:39:02 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/09 15:17:33 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_sort_arr(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;
	int	flag;

	flag = 0;
	i = 0;
	tmp = 0;
	while (++i < size)
	{
		j = -1;
		while (++j < size - i)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = 1;
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	if (flag == 0)
		return (0);
	return (1);
}

int	*ft_stack_to_arr(t_deq *deq, int size)
{
	int		*arr;
	t_node	*node;
	int		i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	node = deq->top;
	while (i < size)
	{
		arr[i] = node->data;
		node = node->next;
		i++;
	}
	return (arr);
}
