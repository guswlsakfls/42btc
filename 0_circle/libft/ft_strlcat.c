/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:13:05 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/04 15:30:58 by hyujo            ###   ########.fr       */
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
	ft_strlcpy(dst + dst_l, src, dstsize - dst_l);
	return (dst_l + src_l);
}
