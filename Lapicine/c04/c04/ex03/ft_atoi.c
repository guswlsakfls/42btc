/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 22:43:11 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/18 18:04:20 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_space(char *str)
{
	if (*str == '\t' || *str == '\f' || *str == '\n')
		return (1);
	else if (*str == '\r' || *str == '\v' || *str == ' ')
		return (1);
	return (0);
}

int	ft_is_minus(char *str)
{
	if (*str == '-')
		return (1);
	return (0);
}

int	ft_is_digit(char *str)
{
	if ('0' <= *str && *str <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	m;

	res = 0;
	m = 1;
	while (ft_is_space(str))
		str++;
	while(*str == '+' || *str == '-')
	{
		if (ft_is_minus(str))
			m *= -1;
		str++;
	}
	while (ft_is_digit(str))
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * m);
}
