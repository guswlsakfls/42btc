/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:33:56 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/31 21:10:13 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->width = 0;
	flags->prec = -1;
	flags->base = 10;
}

int	ft_print_space_or_zero(t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->zero == 1)
	{
		while (--(flags->width) > 0)
			cnt += write(1, "0", 1);
	}
	else
	{
		while (--(flags->width) > 0)
			cnt += write(1, " ", 1);
	}	
	return (cnt);
}

int	ft_type_char(char c, t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	cnt += write(1, &c, 1);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int ft_type_str(char *str, t_flags *flags)
{
	int	cnt;
	int len;

	len = ft_strlen(str);
	cnt = 0;
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

int	ft_print_nbr(long nb)
{
	int	cnt;

	cnt = 0;
	if (nb < 0)
	{
		cnt += write(1, &"-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		cnt += ft_print_nbr(nb / 10);
	cnt += write(1, &"0123456789"[nb % 10], 1);
	return (cnt);
}

unsigned int	ft_print_nbr_u(unsigned int nb)
{
	int	cnt;

	cnt = 0;
	if (nb >= 10)
		cnt += ft_print_nbr(nb / 10);
	cnt += write(1, &"0123456789"[nb % 10], 1);
	return (cnt);
}

int	ft_len_nbr_base(long nb, t_flags *flags)
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

int	ft_type_nbr(long nb, t_flags *flags)
{
	int	cnt;
	int len;

	len = ft_len_nbr_base(nb, flags);
	cnt = 0;
	if (flags->minus == 0)
	{
		if (len < flags->width)
			flags->width = flags->width - len + 1;
		else if (len > flags->width)
			flags->width = 0;
		cnt += ft_print_space_or_zero(flags);
	}
	cnt = ft_print_nbr(nb);
	if (len < flags->width)
		flags->width = flags->width - len + 1;
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

unsigned int	ft_type_nbr_u(unsigned int nb, t_flags *flags)
{
	int	cnt;
	int len;

	len = ft_len_nbr_base(nb, flags);
	cnt = 0;
	if (flags->minus == 0)
	{
		if (len < flags->width)
			flags->width = flags->width - len + 1;
		else if (len > flags->width)
			flags->width = 0;
		cnt += ft_print_space_or_zero(flags);
	}
	cnt = ft_print_nbr_u(nb);
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int	ft_print_nbr_xX(long nb)
{
	int	cnt;

	cnt = 0;
	if (nb < 0)
	{
		cnt += write(1, &"-", 1);
		nb *= -1;
	}
	if (nb >= 8)
		cnt += ft_print_nbr(nb / 8);
	cnt += write(1, &"01234567"[nb % 8], 1);
	return (cnt);
}

int	ft_type_nbr_xX(long nb, t_flags *flags)
{
	int	cnt;
	int len;

	len = ft_len_nbr_base(nb, flags);
	cnt = 0;
	if (flags->minus == 0)
	{
		if (len < flags->width)
			flags->width = flags->width - len + 1;
		else if (len > flags->width)
			flags->width = 0;
		cnt += ft_print_space_or_zero(flags);
	}
	cnt += ft_print_nbr_xX(nb);
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int	ft_print_parsing_type(char **fmt, va_list *ap, t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (**fmt == '%')
		cnt += ft_type_percent(flags);
	else if(**fmt == 'c')
		cnt += ft_type_char(va_arg(*ap, int), flags);
	else if (**fmt == 's')
		cnt += ft_type_str(va_arg(*ap, char *), flags);
	else if (**fmt == 'd' || **fmt == 'i')
		cnt += ft_type_nbr(va_arg(*ap, int), flags);
	else if (**fmt == 'u')
		cnt += ft_type_nbr_u(va_arg(*ap, unsigned int), flags);
	// else if (**fmt == 'p')
	// {
	// 	ft_putaddr(va_arg(ap, int));
	// }
	else if (**fmt == 'x' || **fmt == 'X')
	{
		flags->base = 16;
			cnt += ft_type_nbr_xX(va_arg(*ap, int), flags);
	}
	(*fmt)++;
	return (cnt);
}

int	ft_get_nbr(char **fmt)
{
	int	res;

	res = 0;
	while (**fmt != '\0' && ft_isdigit(**fmt))
	{
		res = res * 10 + **fmt - '0';
		(*fmt)++;
	}
	return (res);
}

void	ft_check_flags(t_flags *flags, char **fmt)
{
	if (**fmt == '-')
		flags->minus = 1;
	else if (**fmt == '0')
		flags->zero = 1;
	else if (ft_isdigit(**fmt))
		flags->width = ft_get_nbr(fmt);
	else if (**fmt == '.')
		flags->prec = 1;
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
			(*fmt)++; // 이 부분을 올린거는 체크 다음에 또 옴기면 다음으로 넘어감.
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
	t_flags	*flags;
	int		cnt;

	va_start(ap, fmt);
	flags = malloc(sizeof(t_flags *));
	if (!flags)
		return (-1);
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
			ft_init_flags(flags);
			cnt += ft_parsing((char **)&fmt, &ap, flags);
		}
	}
	va_end(ap);
	free(flags);
	return (cnt);
}

int	main(void)
{
	int	cnt;

	cnt = 0;
	cnt = printf("%10x\n", 30);
	printf("---------------------------------------\n");
	cnt = ft_printf("%10x\n", 30);
	// printf("%d\n", cnt);
	return (0);
}
