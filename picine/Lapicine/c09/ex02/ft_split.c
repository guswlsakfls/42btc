/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:05:39 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/26 17:12:56 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_str_in_chs(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_word_count(char *str, char *charset)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (ft_str_in_chs(str[i], charset))
			i++;
		if (str[i] && !ft_str_in_chs(str[i], charset))
		{
			while (str[i] && !ft_str_in_chs(str[i], charset))
				i++;
			cnt++;
		}
	}
	return (cnt);
}

void	ft_strcpy(char *res, char *str, int j, int w_len)
{
	int	i;

	i = 0;
	while (w_len != 0)
	{
		res[i] = str[j - w_len];
		w_len--;
		i++;
	}
	res[i] = 0;
}

void	ft_split_str(char **res, char *str, char *charset, int count_str)
{
	int	i;
	int	j;
	int	w_len;

	i = 0;
	w_len = 0;
	j = 0;
	while (str[j] && i < count_str)
	{
		while (str[j] && ft_str_in_chs(str[j], charset))
			j++;
		while (str[j] && !ft_str_in_chs(str[j], charset))
		{
			j++;
			w_len++;
		}
		res[i] = malloc(sizeof(char) * w_len + 1);
		ft_strcpy(res[i], str, j, w_len);
		w_len = 0;
		i++;
	}
	res[i] = NULL;
}

char	**ft_split(char *str, char *charset)
{
	int		count_str;
	char	**res;

	if (str == 0)
		return (NULL);
	count_str = ft_word_count(str, charset);
	res = malloc(sizeof(char *) * (count_str + 1));
	if (res == 0)
		return (NULL);
	ft_split_str(res, str, charset, count_str);
	return (res);
}
