/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:55:12 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/02 17:35:34 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_len(int n)
{
	size_t		len;
	long long	nb;

	nb = n;
	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t		len;
	char		*str;
	long long	nb;

	nb = n;
	len = ft_get_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (n == 0)
		return (ft_strdup("0"));
	if (!str)
		return (0);
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	while (nb > 0)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	str[ft_get_len(n)] = '\0';
	return (str);
}
