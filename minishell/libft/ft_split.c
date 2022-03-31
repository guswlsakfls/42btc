/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:08:57 by dha               #+#    #+#             */
/*   Updated: 2022/03/31 09:01:30 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != '\0' && str[i] != c)
			i++;
		cnt++;
	}
	return (cnt);
}

static char	*split_each(char const *str, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *) ft_malloc(sizeof(char), (len + 1));
	if (word == 0)
		return (0);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	free_words(char **words, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(words[i++]);
	free(words);
	return (0);
}

static void	ft_split_behave(char const *s, char c, char **words)
{
	int	start;
	int	i;
	int	word_i;

	i = 0;
	word_i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		words[word_i] = split_each(s + start, i - start);
		if (words[word_i] == 0)
		{
			free_words(words, word_i);
			return ;
		}
		word_i++;
	}
	words[word_i] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	if (s == NULL)
		return (NULL);
	words = (char **) ft_malloc(sizeof(char *), (count_words(s, c) + 1));
	if (words == 0)
		return (0);
	ft_split_behave(s, c, words);
	return (words);
}
