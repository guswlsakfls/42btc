/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:36:32 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:36:32 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	slen;
	size_t	i;

	slen = 0;
	while (s1[slen])
		slen++;
	if (!(dest = (char *)malloc(sizeof(char) * (slen + 1))))
		return (NULL);
	i = 0;
	while (i < slen)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strnldup(const char *s1)
{
	char	*dest;
	size_t	slen;
	size_t	i;

	slen = 0;
	while (s1[slen] != '\n')
		slen++;
	if (!(dest = (char *)malloc(slen + 1)))
		return (NULL);
	i = 0;
	while (i < slen)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return (str);
}
