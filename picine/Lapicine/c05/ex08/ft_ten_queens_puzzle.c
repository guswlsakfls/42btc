/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:22:49 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/19 00:00:13 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	queens(int *arr, int i, int *cnt);
int		is_promising(int *arr, int i);
void	print_queens(int *arr);

int	ft_ten_queens_puzzle(void)
{
	int	arr[10];
	int i;
	int *cnt;

	i = 0;
	*cnt = 0;
	while (i < 11)
		arr[i++] = 0;
	i = 0;
	queens(arr, i, *cnt);
	return (*cnt);
}

void	queens(int *arr, int i, int *cnt)
{
	int j;

	j = 0;
	while (j < 10)
	{
		arr[i] = j;
		if (i < 10 || is_promising(arr, i))
		{
			if (i == 9)
			{
				*cnt += 1;
				print_queens(arr);
				return ;
			}
			queens(arr, i + 1, *cnt);
		}
	}
}

int	is_promising(int *arr, int i)
{
	while (i != 0)
	{
		if (arr[i] == arr[i - 1])
			return (0);
		else if (arr[i] == arr[i - 1] - 1 || arr[i] == arr[i - 1] + 1)
			return (0);
	}
	return (1);
}

void	print_queens(int *arr)
{
	int i;

	i = 0;
	while (i < 10)
	{
		write(1, &arr[i], 1);
	}
	write(1, "\n", 1);
}
