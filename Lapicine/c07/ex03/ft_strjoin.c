/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:20:44 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/20 22:22:36 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_count_str(char **strs, int size, char *sep)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (i < size)
	{
		cnt += ft_strlen(strs[i]);
		cnt += ft_strlen(sep);
		i++;
	}
	cnt -= ft_strlen(sep);
	return (cnt);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int	count;
	int	i;
	char	*arr;
	char *adr_arr;

	if (size <= 0)
		return (arr = malloc(sizeof(char)));
	count = ft_count_str(strs, size, sep);
	arr = malloc(sizeof(char) * (count + 1));
	if (arr == 0)
		return (0);
	adr_arr = arr;
	i = -1;
	while (++i < size)
	{
		ft_strcpy(adr_arr, strs[i]);
		adr_arr += ft_strlen(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(adr_arr, sep);
			adr_arr += ft_strlen(sep);
		}
	}
	*adr_arr = '\0';
	return (arr);
}
