/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:52:45 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/07 17:59:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	ft_check_over(unsigned long long sum, int sign)
{
	if (sum > 9223372036854775807 - 1 && sign == -1)
		exit(0);
	if (sum > 9223372036854775807 && sign == 1)
		exit(0);
	return (sum * sign);
}

static int	ft_issapce(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

long long	ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long long	res;

	i = 0;
	while (ft_issapce(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	res = 0;
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	res = ft_check_over(res, sign);
	return (res);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}
