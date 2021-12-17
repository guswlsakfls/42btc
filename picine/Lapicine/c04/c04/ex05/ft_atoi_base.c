/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:57:34 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/18 22:35:54 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_space(int c)
{
	if ((c == ' ' || c == '\t' || c == '\n'))
		return (1);
	if ((c == '\v' || c == '\f' || c == '\r'))
		return (1);
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_base_error(char *base, int b_len)
{
	int i;
	int j;

	i = -1;
	if (b_len <= 1)
		return (1);
	while (++i < b_len)
	{
		if (ft_is_space(base[i]))
			return (1);
	}
	i = -1;
	while (++i < b_len)
	{
		j = i + 1;
		while (j < b_len)
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		if (base[i] == '-' || base[i] == '+')
			return (1);
	}
	return (0);
}

int	ft_is_base(char *str, char *base)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (base[i])
		{
			if (base[i] == *str)
				return (i);
			i++;
		}
		str++;
	}
	return (-1);
}

int		ft_atoi_base(char *str, char *base)
{
	int b_len;
	int res;
	int	m;

	m = 1;
	res = 0;
	b_len = ft_strlen(base);
	if (ft_base_error(base, b_len))
		return (0);
	while (ft_is_space(*str))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m *= -1;
		str++;
	}
	while (ft_is_base(str, base) >= 0)
	{
		res = res * b_len + ft_is_base(str, base);
		str++;
	}
	return (res * m);
}
