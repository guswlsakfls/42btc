/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:19:46 by dha               #+#    #+#             */
/*   Updated: 2022/03/10 18:46:16 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_len(char *s, int *unclosed)
{
	char	*start;
	// char	*word;

	start = s;
	while (*s != '\0')
	{
		if (is_symbol(start))
		{
			s += is_symbol(start);
			break;
		}
		*unclosed ^= (*s == '\'') << 1;
		*unclosed ^= (*s == '\"') << 2;
		*unclosed |= (!(*unclosed) && (*s == '\\' || *s == ';')) << 3;
		s++;
		if (!(*unclosed) && (*s == ' ' || is_symbol(s)))
			break ;
	}
	if (*unclosed)
		return (0);
	return (s - start);
}

int	cnt_words(char *s)
{
	int		cnt;
	int		unclosed;
	int		cmd_len;

	cnt = 0;
	while (*s != '\0')
	{
		unclosed = 0;
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break ;
		cmd_len = get_cmd_len(s, &unclosed);
		if (!cmd_len)
			ft_error_exit("Error\n Invalid symbol included");
		s += cmd_len;
		cnt++;
	}
	return (cnt);
}

char	**cmd_split(char *s)
{
	char	**words;
	char	*word;
	int		cmd_len;
	int		idx;
	int		unclosed;

	words = (char **) malloc(sizeof(char *) * (cnt_words(s) + 1));
	idx = 0;
	while (*s != '\0')
	{
		unclosed = 0;
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break ;
		cmd_len = get_cmd_len(s, &unclosed);
		word = ft_calloc(cmd_len, sizeof(char));
		strlcpy(word, s, cmd_len + 1);
		words[idx++] = word;
		s += cmd_len;
	}
	words[idx] = NULL;
	return (words);
}


t_list	*tokenize(char *cmd)
{
	char	**cmds;
	t_list	*token_lst;
	t_token	*token;
	int		i;

	i = 0;
	cmds = cmd_split(cmd);
	token_lst = NULL;
	// while (cmds[i])
	// 	printf("%s\n", cmds[i++]);
	while (cmds[i])
	{
		token = malloc(sizeof(t_token));
		bzero(token, sizeof(t_token));
		token->str = cmds[i];
		token->type |= token_type(cmds[i]);
		// printf("%d: %d, %s\n", i, token->type, token->str);
		ft_lstadd_back(&token_lst, ft_lstnew(token));
		i++;
	}
	return (token_lst);
}
