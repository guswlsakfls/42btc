/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_di_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:51:43 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/06 19:11:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	ft_len_base(long nb, int base)
{
	int	len;

	len = 0;
	while (nb > 0)
	{
		nb = nb / base;
		len++;
	}
	return (len);
}

int	ft_type_di(long nb, t_flags *flags)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags->deci);
	cnt = 0;
	if (len > flags->width)
		flags->width = 0;
	flags->prec += 1 - len;
	if (flags->prec > 0)
		flags->width += 1 - flags->prec;
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	if (flags->plus == 1)
		cnt += write(1, "+", 1);
	if (flags->space == 1)
		cnt += write(1, " ", 1);
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	while (--(flags->prec) > 0)
		cnt += write(1, "0", 1);
	cnt += ft_print_di(nb);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

unsigned int	ft_type_u(unsigned int nb, t_flags *flags)
{
	int	cnt;
	int	len;

	len = ft_len_base(nb, flags->deci);
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
	while (--(flags->prec) > 0)
		cnt += write(1, "0", 1);
	cnt += ft_print_u(nb);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}
