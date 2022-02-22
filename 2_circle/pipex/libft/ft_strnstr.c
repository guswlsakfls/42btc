/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:38:12 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/02 18:52:12 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nee_len;
	size_t	i;

	nee_len = ft_strlen(needle);
	if (!nee_len)
		return ((char *)haystack);
	if (!len)
		return (0);
	i = 0;
	while (haystack[i] && i <= len - nee_len)
	{
		if (!ft_strncmp(haystack + i, needle, nee_len))
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
