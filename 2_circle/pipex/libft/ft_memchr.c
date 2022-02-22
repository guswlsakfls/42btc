/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:20:48 by hyujo             #+#    #+#             */
/*   Updated: 2021/11/29 11:17:09 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*mem_s;

	mem_s = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (mem_s[i] == (const unsigned char)c)
			return ((void *)mem_s + i);
		i++;
	}
	return (0);
}
