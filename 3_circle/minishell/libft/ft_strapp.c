/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:54:04 by dha               #+#    #+#             */
/*   Updated: 2022/03/18 21:28:21 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ordi_apply(char *s1, char *s2)
{
	size_t	len;
	size_t	s1_len;
	size_t	i;
	char	*str;

	s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2) + 2;
	str = ft_malloc(sizeof(char), len);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = ' ';
	while (i < len)
	{
		str[i] = s2[i - (s1_len + 1)];
		i++;
	}
	free(s1);
	return (str);
}

static char	*init_apply(char *s2)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = ft_strlen(s2) + 1;
	str = ft_malloc(sizeof(char), len);
	i = 0;
	while (i < len)
	{
		str[i] = s2[i];
		i++;
	}
	return (str);
}

char	*ft_strapp(char *s1, char *s2)
{
	if (s1)
		return (ordi_apply(s1, s2));
	else
		return (init_apply(s2));
}
