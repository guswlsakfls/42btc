/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:33:56 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/03 15:51:50 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

t_flags	ft_init_flags(void)
{
	t_flags	flags;

	flags.minus = 0;
	flags.zero = 0;
	flags.width = 0;
	flags.prec = 0;
	flags.base = 10;
	return (flags);
}

int	ft_print_space_or_zero(t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->width > 0)
	{
		while (--(flags->width) > 0)
			cnt += write(1, " ", 1);
	}	
	if (flags->zero == 1 || flags->prec > 0)
	{
		while (--(flags->width) > 0 || --(flags->prec) > 0)
			cnt += write(1, "0", 1);
	}
	return (cnt);
}

int	ft_type_char(char c, t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->zero == 1)
		return (-1);
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	cnt += write(1, &c, 1);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int	ft_type_str(char *str, t_flags *flags)
{
	int	cnt;
	int	len;

	len = ft_strlen(str);
	cnt = 0;
	if (flags->zero == 1)
		return (-1);
	if (flags->prec == 1)
		flags->width = 0;
	if (flags->minus == 0)
	{
		if (len < flags->width)
			flags->width = flags->width - len + 1;
		else if (len > flags->width)
			flags->width = 0;
		cnt += ft_print_space_or_zero(flags);
	}
	cnt += write(1, str, len);
	if (len < flags->width)
	{
		flags->width = flags->width - len + 1;
		cnt += ft_print_space_or_zero(flags);
	}
	return (cnt);
}

int	ft_print_di(long nb)
{
	int	cnt;

	cnt = 0;
	if (nb < 0)
	{
		cnt += write(1, &"-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		cnt += ft_print_di(nb / 10);
	cnt += write(1, &"0123456789"[nb % 10], 1);
	return (cnt);
}

unsigned int	ft_print_u(unsigned int nb)
{
	int	cnt;

	cnt = 0;
	if (nb >= 10)
		cnt += ft_print_di(nb / 10);
	cnt += write(1, &"0123456789"[nb % 10], 1);
	return (cnt);
}

int	ft_len_base(long nb, t_flags *flags)
{
	int	len;

	len = 0;
	while (nb > 0)
	{
		nb = nb / flags->base;
		len++;
	}
	return (len);
}

int	ft_type_di(long nb, t_flags *flags)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags);
	cnt = 0;
	flags->prec += 1 - len;
	if (len < flags->width)
		flags->width = flags->width - flags->prec + 2;
	if (flags->minus == 0)
	{
		if (len > flags->width)
			flags->width = 0;
		cnt += ft_print_space_or_zero(flags);
	}
	while (--(flags->prec) > 0)
		cnt += write(1, "0", 1);
	cnt += ft_print_di(nb);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int	ft_type_percent(t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	cnt += write(1, &"%", 1);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

unsigned int	ft_type_u(unsigned int nb, t_flags *flags)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags);
	cnt = 0;
	if (flags->minus == 0)
	{
		if (len < flags->width)
			flags->width = flags->width - len + 1;
		else if (len > flags->width)
			flags->width = 0;
		cnt += ft_print_space_or_zero(flags);
	}
	cnt = ft_print_u(nb);
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int	ft_print_xX(long nb, char *fmt)
{
	int	cnt;

	cnt = 0;
	if (nb < 0)
	{
		cnt += write(1, &"-", 1);
		nb *= -1;
	}
	if (nb >= 16)
		cnt += ft_print_xX(nb / 16, fmt);
	if (*fmt == 'x')
		cnt += write(1, &"0123456789abcdef"[nb % 16], 1);
	else if (*fmt == 'X')
		cnt += write(1, &"0123456789ABCDEF"[nb % 16], 1);
	return (cnt);
}

int	ft_type_xX(long nb, t_flags *flags, char *fmt)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags);
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	else if (len > flags->width)
		flags->width = 0;
	cnt = 0;
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	cnt += ft_print_xX(nb, fmt);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int	ft_print_p(unsigned long nb)
{
	int	cnt;

	cnt = 0;
	if (nb >= 16)
		cnt += ft_print_p(nb / 16);
	cnt += write(1, &"0123456789abcdef"[nb % 16], 1);
	return (cnt);
}

int	ft_type_addr(unsigned long nb, t_flags *flags)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags);
	flags->width -= 2;
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	else if (len > flags->width)
		flags->width = 0;
	cnt = 0;
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	cnt += write(1, "0x", 2);
	cnt += ft_print_p(nb);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
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
	{
		flags->base = 16;
		cnt += ft_type_addr(va_arg(*ap, unsigned long), flags);
	}
	else if (**fmt == 'x' || **fmt == 'X')
	{
		flags->base = 16;
		cnt += ft_type_xX(va_arg(*ap, int), flags, *fmt);
	}
	(*fmt)++;
	return (cnt);
}

int	ft_to_nbr(char **fmt)
{
	int	res;

	res = 0;
	while (**fmt != '\0' && ft_isdigit(**fmt))
	{
		res = res * 10 + **fmt - '0';
		(*fmt)++;
	}
	(*fmt)--;
	return (res);
}

void	ft_check_flags(t_flags *flags, char **fmt)
{
	if (**fmt == '-')
		flags->minus = 1;
	else if (**fmt == '0')
		flags->zero = 1;
	else if (ft_isdigit(**fmt))
		flags->width = ft_to_nbr(fmt);
	else if (**fmt == '.')
	{
		(*fmt)++;
		flags->prec = ft_to_nbr(fmt);
	}
}

int	ft_parsing(char **fmt, va_list *ap, t_flags *flags)
{
	int		cnt;
	char	percent;

	percent = '%';
	cnt = 0;
	while (**(fmt) != '\0')
	{
		while (!ft_strchr("cspdiuxX", **fmt) && **fmt != '\0')
		{
			(*fmt)++;
			ft_check_flags(flags, fmt);
			if (**fmt == percent)
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

int	main(void)
{
	int	cnt;

	cnt = 0;
	cnt = printf("%010.2dd\n", 100);
	printf("cnt : %d\n", cnt);
	printf("---------------------------------------\n");
	cnt = ft_printf("%010.2dd\n", 100);
	printf("cnt : %d\n", cnt);
	return (0);
}
