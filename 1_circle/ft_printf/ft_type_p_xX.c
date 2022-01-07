/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_p_xX.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:02:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/06 19:11:46 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_xX(unsigned long nb, char *fmt)
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

int	ft_type_xX(unsigned long nb, t_flags *flags, char *fmt)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags->hex);
	cnt = 0;
	if (len > flags->width)
		flags->width = 0;
	flags->prec += 1 - len;
	if (flags->prec > 0)
		flags->width += 1 - flags->prec;
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	if (flags->hash == 1 && *fmt == 'x')
		cnt += write(1, "0x", 2);
	else if (flags->hash == 1 && *fmt == 'X')
		cnt += write(1, "0X", 2);
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

int	ft_type_p(unsigned long nb, t_flags *flags)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags->hex);
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
