/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:37:23 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/11 17:43:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_combn(int n);
{
	int i;
	char numbers[10];

	i = 0;
	while (i < n)
	{
		numbers[i] = i + '0';
	}
	if (numbers[i] != '10')
	{
		ft_putchar(numbers[i]);
		if (numbers[
		ft_putchar(',');
		ft_putchar(' ');
		numbers[i]++;
	}

