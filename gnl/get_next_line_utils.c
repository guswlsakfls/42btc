/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:24:00 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/12 19:27:42 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		s++;
		cnt++;
	}
	return (cnt);
}

char	*ft_strdup(const char *s)
{
	size_t			i;
	size_t			len;
	unsigned char	*ptr;

	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)s[i];
		i++;
	}
	ptr[i] = '\0';
	return ((char *)ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;

	len_src = 0;
	while (src[len_src] != '\0')
		len_src++;
	if (!dstsize)
		return (len_src);
	i = 0;
	while (src[i] != '\0' && (i + 1) < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_src);
}

char	*ft_strchr(const char *s, int c)
{
	size_t				i;
	size_t				len;
	const unsigned char	*str;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	str = (const unsigned char *)s;
	while (i < len)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(str + s1_len, s2, s2_len + 1);
	return (str);
}
