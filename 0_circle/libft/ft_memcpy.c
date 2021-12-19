/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:59 by hyujo             #+#    #+#             */
/*   Updated: 2021/11/29 10:46:25 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*addr_src;
	unsigned char		*addr_dst;
	size_t				i;

	i = 0;
	addr_dst = (unsigned char *)dst;
	addr_src = (const unsigned char *)src;
	if (n == 0 || addr_dst == addr_src)
		return (dst);
	while (i < n)
	{
		addr_dst[i] = addr_src[i];
		i++;
	}
	return (dst);
}
