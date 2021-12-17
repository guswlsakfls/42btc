/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:42:20 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/25 11:15:26 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str);
int	ft_whitespace(char c);
int	ft_base_erorr(char *base, int b_len);
int	ft_is_from(char *nbr, char *b_from);

int	ft_atoi_base(char *nbr, char *b_from, int f_len)
{
	int	m;
	int	res;

	res = 0;
	m = 1;
	while (ft_whitespace(*nbr))
		nbr++;
	while (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			m *= -1;
		nbr++;
	}
	while (ft_is_from(nbr, b_from) >= 0)
	{
		res = res * f_len + ft_is_from(nbr, b_from);
		nbr++;
	}
	return (res * m);
}

int	ft_make_size(long long tmp, int t_len)
{
	int	size;

	size = 0;
	if (tmp < 0)
		tmp *= -1;
	while (tmp >= t_len)
	{
		tmp /= t_len;
		size++;
	}
	size++;
	return (size);
}

void	ft_getnbr_to(long long n, char *base_to, int size, char *str)
{
	int	i;
	int	t_len;

	t_len = ft_strlen(base_to);
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	if (str[0] == '-')
		size++;
	while (n >= t_len)
	{
		str[size  - i - 1] = base_to[n % t_len];
		n = n / t_len;
		i++;
	}
	str[size - i - 1] = base_to[n % t_len];
	str[size] = '\0';
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int	f_len;
	int	t_len;
	char	*str;
	int		size;
	long long	n;

	f_len = ft_strlen(base_from);
	t_len = ft_strlen(base_to);
	if (ft_base_erorr(base_from, f_len) || ft_base_erorr(base_to, t_len))
		return (0);
	n = ft_atoi_base(nbr, base_from, f_len);
	size = ft_make_size(n, t_len);
	str = malloc(sizeof(char) * size + 1);
	str[0] = 0;
	if (size == 0)
		return (NULL);
	ft_getnbr_to(n, base_to, size, str);
	return (str);
}
