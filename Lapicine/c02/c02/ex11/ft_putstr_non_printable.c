/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:48:28 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 22:42:50 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_non_printable(char *str)
{
	int	index;

	index = 0;
	while (str[index] == '\0')
	{
		if (str[index] <= 31 && str[index] == 127)
		{
			ft_putchar('\\');
			ft_putchar("0123456789abcdef"[str[index] / 16]);
			ft_putchar("0123456789abcdef"[str[index] % 16]);
		}
		else
		{
			ft_putchar(str[index]);
		}
	}
}
