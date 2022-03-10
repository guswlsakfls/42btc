/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_utils_tmp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:19:46 by dha               #+#    #+#             */
/*   Updated: 2022/03/10 17:56:28 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char const *s, int *unclosed)
{
	char const	*start;
	char		*word;
	int			diff;

	start = s;
	while (*s != '\0')
	{
		{
			if (!(*unclosed) && *s == ' ')
				break ;
			*unclosed ^= (*s == '\'') << 1;
			*unclosed ^= (*s == '\"') << 2;
			*unclosed |= (!(*unclosed) && (*s == '\\' || *s == ';')) << 3;
			s++;
		}
	}
	if (*unclosed)
		return (NULL);
	diff = s - start - (2 * (*start == '\'' || *start == '\"'));
	word = malloc(sizeof(char) * diff + 1);
	if (!word)
		ft_error_exit("Error\n Malloc Failed");
	strlcpy(word, start + (*start == '\'' || *start == '\"'), diff + 1);
	return (word);
}

int	cnt_words(char const *s)
{
	int		cnt;
	int		unclosed;
	char	*word;

	cnt = 0;
	while (*s != '\0')
	{
		unclosed = 0;
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break ;
		word = get_word(s, &unclosed);
		s += ft_strlen(word) + (2 * (*s == '\'' || *s == '\"'));
		free(word);
		cnt++;
	}
	return (cnt);
}

char	**cmd_split(char const *s)
{
	char	**words;
	char	*word;
	int		cnt;
	int		idx;
	int		unclosed;

	cnt = cnt_words(s);
	words = (char **) malloc(sizeof(char *) * (cnt + 1));
	if (!words)
		return (0);
	words[cnt] = NULL;
	idx = 0;
	while (*s != '\0')
	{
		unclosed = 0;
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break ;
		word = get_word(s, &unclosed);
		words[idx] = word;
		s += ft_strlen(word) + (2 * (*s == '\'' || *s == '\"'));
		idx++;
	}
	return (words);
}
