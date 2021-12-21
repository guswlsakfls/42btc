/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:40:42 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/18 20:55:33 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_base_error(char *str)
{
	int i;
	int j;

	i = 0;
	if (str[i] == 0 || ft_strlen(str) <= 1)
		return (1);
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
			return (1);
		if (str[i] == '\r' || str[i] == '+' || str[i] == '-')
			return (1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		j = i;
		while (++j < ft_strlen(str))
			if (str[i] == str[j])
				return (1);
		i++;
	}
	return (0);
}

void	ft_print_base(long long nb, char *base, int b_len)
{
	if (nb >= b_len)
	{
		ft_print_base(nb / b_len, base, b_len);
		write(1, &base[nb % b_len], 1);
	}
	else if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
		ft_print_base(nb, base, b_len);
	}
	else
	{
		write(1, &base[nb % b_len], 1);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	b_len;

	if (check_base_error(base))
		return ;
	b_len = ft_strlen(base);
	ft_print_base(nbr, base, b_len);
}
