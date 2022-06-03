/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:31:49 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/26 17:53:35 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cmp_s1;
	const unsigned char	*cmp_s2;

	cmp_s1 = (const unsigned char *)s1;
	cmp_s2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (cmp_s1[i] && cmp_s2[i] && i + 1 < n)
	{
		if (cmp_s1[i] != cmp_s2[i])
			return (cmp_s1[i] - cmp_s2[i]);
		i++;
	}
	return (cmp_s1[i] - cmp_s2[i]);
}

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
	return (NULL);
}
