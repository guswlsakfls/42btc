/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:59 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/04 15:30:43 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*mem_src;
	unsigned char		*mem_dst;
	size_t				i;

	i = 0;
	mem_dst = (unsigned char *)dst;
	mem_src = (const unsigned char *)src;
	if (n == 0 || mem_dst == mem_src)
		return (dst);
	while (i < n)
	{
		mem_dst[i] = mem_src[i];
		i++;
	}
	return (dst);
}
