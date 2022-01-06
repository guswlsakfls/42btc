/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_pct_c_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:45:40 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/06 16:53:52 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type_percent(t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->prec > 0)
		flags->width = flags->width - flags->prec + 1;
	if (flags->minus == 0)
		cnt += ft_print_space_or_zero(flags);
	cnt += write(1, &"%", 1);
	cnt += ft_print_space_or_zero(flags);
	return (cnt);
}

int	ft_type_char(char c, t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->zero == 1)
		return (ERR);
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

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	cnt = 0;
	if (flags->prec < len)
		len = flags->prec;
	if (len < flags->width)
		flags->width = flags->width - len + 1;
	flags->prec = 0;
	if (flags->minus == 0)
	{
		if (len > flags->width)
			flags->width = 0;
		cnt += ft_print_space_or_zero(flags);
	}
	cnt += write(1, str, len);
	if (len < flags->width)
		cnt += ft_print_space_or_zero(flags);
	return (cnt);
}
