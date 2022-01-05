/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:50:22 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/21 15:35:33 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_malloc_error(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
	str = NULL;
	return (NULL);
}

static size_t	ft_check_c(char str, char chr)
{
	if (str == chr)
		return (1);
	return (0);
}

static size_t	ft_word_count(char const *str, char chr)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (ft_check_c(str[i], chr))
			i++;
		if (str[i] && !ft_check_c(str[i], chr))
		{
			while (str[i] && !ft_check_c(str[i], chr))
				i++;
			cnt++;
		}
	}
	return (cnt);
}

char	**ft_work_split(char **res, char const *str, char chr, size_t s_cnt)
{
	size_t	res_i;
	size_t	str_i;
	size_t	word_len;

	res_i = 0;
	str_i = 0;
	while (str[str_i] && res_i < s_cnt)
	{
		word_len = 0;
		while (str[str_i] && ft_check_c(str[str_i], chr))
			str_i++;
		while (str[str_i] && !ft_check_c(str[str_i], chr))
		{
			str_i++;
			word_len++;
		}
		res[res_i] = malloc(sizeof(char) * (word_len + 1));
		if (res == NULL)
			return (ft_malloc_error(res));
		ft_strlcpy(res[res_i], str + str_i - word_len, word_len + 1);
		res_i++;
	}
	res[s_cnt] = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	w_cnt;
	char	**res;

	if (s == 0)
		return (NULL);
	w_cnt = ft_word_count(s, c);
	res = malloc(sizeof(char *) * (w_cnt + 1));
	if (res == 0)
		return (NULL);
	ft_work_split(res, s, c, w_cnt);
	return (res);
}
