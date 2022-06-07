/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:36:41 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:36:41 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

static	void	freestr(char **str, size_t index)
{
	while (index--)
	{
		free(str[index]);
		str[index] = NULL;
	}
	free(str);
	str = NULL;
}

static	size_t	hms(const char *s, char c)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			result++;
		}
	}
	return (result);
}

size_t			endcount(const char *s, char c, size_t end)
{
	while (s[end] != c && s[end])
		end++;
	return (end);
}

static char		**splitcpy(char **str, const char *s, char c, size_t hmsplit)
{
	size_t	index;
	size_t	start;
	size_t	end;

	index = 0;
	end = 0;
	while (s[end] == c && s[end])
		end++;
	while (index < hmsplit)
	{
		start = end;
		end = endcount(s, c, end);
		str[index] = malloc(sizeof(char) * (end - start + 1));
		if (!str[index])
		{
			freestr(str, index);
			return (NULL);
		}
		ft_strlcpy(str[index], s + start, end - start + 1);
		while (s[end] == c)
			end++;
		index++;
	}
	str[hmsplit] = NULL;
	return (str);
}

char			**ft_split(const char *s, char c)
{
	char	**str;
	size_t	hmsplit;

	if (!s)
		return (NULL);
	hmsplit = hms(s, c);
	str = malloc(sizeof(char *) * (hmsplit + 1));
	if (!str)
		return (NULL);
	if (!splitcpy(str, s, c, hmsplit))
		return (NULL);
	return (str);
}
