/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:13:05 by hyujo             #+#    #+#             */
/*   Updated: 2021/11/29 17:43:54 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_l;
	size_t	dst_l;

	src_l = ft_strlen(src);
	dst_l = ft_strlen(dst);
	if (dst_l >= dstsize)
		return (src_l + dstsize);
	i = 0;
	while (src[i] && (i + 1) < dstsize - dst_l)
	{
		dst[dst_l + i] = src[i];
		i++;
	}
	dst[dst_l + i] = '\0';
	return (dst_l + src_l);
}
