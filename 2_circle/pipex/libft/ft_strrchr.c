/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:33:34 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/04 15:31:24 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t				len;
	size_t				i;
	const unsigned char	*str;

	i = 0;
	str = (const unsigned char *)s;
	len = ft_strlen(s);
	while (len >= i)
	{
		if (str[len - i] == (unsigned char)c)
			return ((char *)str + len - i);
		i++;
	}
	return (0);
}
