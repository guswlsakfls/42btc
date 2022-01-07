/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:43:49 by hyujo             #+#    #+#             */
/*   Updated: 2021/11/29 11:02:11 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*mem_src;
	unsigned char		*mem_dst;
	size_t				i;

	mem_src = (const unsigned char *)src;
	mem_dst = (unsigned char *)dst;
	i = 0;
	if (len == 0 || mem_dst == mem_src)
		return (dst);
	if (mem_dst > mem_src)
	{
		while (i < len)
		{
			mem_dst[len - i - 1] = mem_src[len - i - 1];
			i++;
		}
	}
	else
		ft_memcpy(mem_dst, mem_src, len);
	return (dst);
}
