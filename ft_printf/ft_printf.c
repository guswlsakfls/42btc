/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:33:56 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/21 19:58:55 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_parsing(char *input, va_list ap)
{
	while (*input != '\0')
	{
		if (*input == 'd' || *input == 'i' || *input == 'u')
		{
			ft_putnbr_fd(va_arg(ap, int), 1);
			return ;
		}
		else if (*input == 'c')
		{
			ft_putchar_fd(va_arg(ap, int), 1);
			return ;
		}
		else if (*input == 's')
		{
			ft_putstr_fd(va_arg(ap, char *), 1);
		}
		else if (*input == 'o')
		{
			ft_putnbr_base(va_arg(ap, int), 8);
		}
		else if (*input == 'p')
		{
			ft_putaddr(va_arg(ap, int));
		}
		else if (*input == 'x' || *input == 'X')
		{
			ft_putnbr_base(va_arg(ap, int), 16);
		}
	input+;
	}
	return ;
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		cnt;

	va_start(ap, input);
	cnt = 0;
	while (*input != '\0')
	{
		if (*input != '%')
		{
			ft_putchar_fd(*input, 1);
			input++;
			continue ;
		}
		else if (*input == '%')
		{
			ft_parsing((char *)input, ap);
			input++;
		}
		input++;
	}
	va_end(ap);
	return (cnt);
}

int	main(void)
{
	//printf("%10d next", 12);
	ft_printf("%d%d%c%s next", 1, 2, 'a', "bcdef");
	return (0);
}
