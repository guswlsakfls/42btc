/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:19:46 by dha               #+#    #+#             */
/*   Updated: 2022/03/20 22:31:47 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_cmd_len(char *s)
{
	char *start;
	int opened;

	start = s;
	opened = 0;
	if (is_symbol(start))
		return (is_symbol(start));
	while (*s != '\0')
	{
		if (!opened && (*s == ' ' || is_symbol(s)))
			break;
		opened ^= (*s == '\'') << 1;
		opened ^= (*s == '\"') << 2;
		opened |= (!opened && (*s == '\\' || *s == ';')) << 3;
		s++;
	}
	if (opened)
		return (0);
	return (s - start);
}

int cnt_words(char *s)
{
	int cnt;
	int cmd_len;

	cnt = 0;
	while (*s != '\0')
	{
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break;
		cmd_len = get_cmd_len(s);
		if (!cmd_len)
			return (0);
		s += cmd_len;
		cnt++;
	}
	return (cnt);
}

char **cmd_split(char *s)
{
	char **words;
	char *word;
	int cmd_len;
	int word_cnt;
	int idx;

	word_cnt = cnt_words(s);
	if (word_cnt == 0)
		return (NULL);
	words = (char **)ft_malloc(sizeof(char *), word_cnt + 1);
	idx = 0;
	while (*s != '\0')
	{
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break;
		cmd_len = get_cmd_len(s);
		word = ft_malloc(sizeof(char), cmd_len);
		strlcpy(word, s, cmd_len + 1);
		words[idx++] = word;
		s += cmd_len;
	}
	words[idx] = NULL;
	return (words);
}

t_list *tokenize(char *cmd)
{
	char **cmds;
	t_list *token_lst;
	t_token *token;
	int i;

	i = 0;
	cmds = cmd_split(cmd);
	token_lst = NULL;
	while (cmds[i])
	{
		token = (t_token *)ft_malloc(sizeof(t_token), 1);
		token->str = cmds[i];
		token->type |= token_type(cmds[i]);
		ft_lstadd_back(&token_lst, ft_lstnew(token));
		i++;
	}
	free(cmds);
	return (token_lst);
}