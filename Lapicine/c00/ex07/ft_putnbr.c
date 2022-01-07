/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:45:30 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/11 16:23:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-');
		ft_putnbr(nb);
	}
	else if (nb == 0)
	{
		ft_putchar('0');
	}
	else if (nb < 10)
	{
		nb = nb + '0';
		ft_putchar(nb);
	}
	else
	{
		ft_putnbr(nb % 10);
		ft_putnbr(nb /= 10);
	}
}

void	putchar(char c)
{
	write(1, &c, 1);
}

int main(void)
{
	ft_putnbr(42);
	return 0;
}
