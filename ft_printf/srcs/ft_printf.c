/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:33:56 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/06 17:38:53 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	ft_init_flags(void)
{
	t_flags	flags;

	flags.minus = 0;
	flags.zero = 0;
	flags.width = 0;
	flags.prec = 0;
	flags.deci = 10;
	flags.hex = 16;
	flags.plus = 0;
	flags.space = 0;
	flags.hash = 0;
	return (flags);
}

int	ft_print_parsing_type(char **fmt, va_list *ap, t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (**fmt == '%')
		cnt += ft_type_percent(flags);
	else if (**fmt == 'c')
		cnt += ft_type_char(va_arg(*ap, int), flags);
	else if (**fmt == 's')
		cnt += ft_type_str(va_arg(*ap, char *), flags);
	else if (**fmt == 'd' || **fmt == 'i')
		cnt += ft_type_di(va_arg(*ap, int), flags);
	else if (**fmt == 'u')
		cnt += ft_type_u(va_arg(*ap, unsigned int), flags);
	else if (**fmt == 'p')
		cnt += ft_type_p(va_arg(*ap, unsigned long), flags);
	else if (**fmt == 'x' || **fmt == 'X')
		cnt += ft_type_xX(va_arg(*ap, unsigned int), flags, *fmt);
	(*fmt)++;
	return (cnt);
}

int	ft_parsing(char **fmt, va_list *ap, t_flags *flags)
{
	int		cnt;

	cnt = 0;
	while (**(fmt) != '\0')
	{
		while (!ft_strchr("cspdiuxX", **fmt) && **fmt != '\0')
		{
			(*fmt)++;
			ft_check_flags(flags, fmt);
			if (**fmt == '%')
				break ;
		}
		if (ft_strchr("%cspdiuxX", **fmt))
		{
			cnt += ft_print_parsing_type(fmt, ap, flags);
			break ;
		}
		(*fmt)++;
	}
	return (cnt);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	t_flags	flags;
	int		cnt;

	va_start(ap, fmt);
	cnt = 0;
	while (*fmt != '\0')
	{
		if (*fmt != '%')
		{
			cnt += write(1, fmt, 1);
			fmt++;
		}
		else if (*fmt == '%')
		{
			flags = ft_init_flags();
			cnt += ft_parsing((char **)&fmt, &ap, &flags);
		}
	}
	va_end(ap);
	return (cnt);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	cnt;

// 	cnt = 0;
// 	cnt = printf("%010.2u\n", 12345);
// 	cnt = printf("%10.3s\n", "12345");
// 	printf("cnt : %d\n", cnt);
// 	printf("---------------------------------------\n");
// 	cnt = ft_printf("%010.2u\n", 12345);
// 	cnt = ft_printf("%10.3s\n", "12345");
// 	printf("cnt : %d\n", cnt);
// 	return (0);
// }
