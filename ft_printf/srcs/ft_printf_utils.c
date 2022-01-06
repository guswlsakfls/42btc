/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:06:10 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/06 17:02:06 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_space_or_zero(t_flags *flags)
{
	int	cnt;

	cnt = 0;
	if (flags->width > 0)
	{
		while (--(flags->width) > 0)
			cnt += write(1, " ", 1);
	}	
	if ((flags->zero == 1 || flags->prec > 0) && flags->minus != 1)
	{
		while (--(flags->width) > 0 || --(flags->prec) > 0)
			cnt += write(1, "0", 1);
	}
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
	else if (**fmt == '+')
		flags->plus = 1;
	else if (**fmt == ' ')
		flags->space = 1;
	else if (**fmt == '#')
		flags->hash = 1;
}
