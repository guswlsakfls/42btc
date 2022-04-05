/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:19:46 by dha               #+#    #+#             */
/*   Updated: 2022/04/01 18:26:28 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_len(char *s, t_list *envs)
{
	char	*start;
	int		opened;

	start = s;
	opened = 0;
	if (is_symbol(start))
		return (is_symbol(start));
	while (*s != '\0')
	{
		if (!opened && (*s == ' ' || is_symbol(s)))
			break ;
		opened ^= (*s == '\'' && !(opened & 2));
		opened ^= (*s == '\"' && !(opened & 1)) << 1;
		s++;
	}
	if (opened)
	{
		if (opened & 1)
			ft_putendl_fd("nano: single quote is not closed", 2);
		if (opened & 2)
			ft_putendl_fd("nano: double quote is not closed", 2);
		set_exit_status(1, envs);
		return (0);
	}
	return (s - start);
}

static int	cnt_words(char *s, t_list *envs)
{
	int		cnt;
	int		cmd_len;

	cnt = 0;
	while (*s != '\0')
	{
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break ;
		cmd_len = get_cmd_len(s, envs);
		if (!cmd_len)
			return (0);
		s += cmd_len;
		cnt++;
	}
	return (cnt);
}

char	**cmd_split(char *s, t_list *envs)
{
	char	**words;
	char	*word;
	int		cmd_len;
	int		word_cnt;
	int		idx;

	word_cnt = cnt_words(s, envs);
	if (word_cnt == 0)
		return (NULL);
	words = (char **) ft_malloc(sizeof(char *), word_cnt + 1);
	idx = 0;
	while (*s != '\0')
	{
		while (*s == ' ')
			s++;
		if (*s == '\0')
			break ;
		cmd_len = get_cmd_len(s, envs);
		word = ft_malloc(sizeof(char), cmd_len + 1);
		ft_strlcpy(word, s, cmd_len + 1);
		words[idx++] = word;
		s += cmd_len;
	}
	words[idx] = NULL;
	return (words);
}

t_list	*tokenize(char *cmd, t_list *envs)
{
	char	**cmds;
	t_list	*token_lst;
	t_token	*token;
	int		i;

	i = 0;
	token_lst = NULL;
	cmds = cmd_split(cmd, envs);
	if (cmds == NULL)
		return (NULL);
	while (cmds[i])
	{
		token = (t_token *) ft_malloc(sizeof(t_token), 1);
		token->str = cmds[i];
		token->type |= token_type(cmds[i]);
		ft_lstadd_back(&token_lst, ft_lstnew(token));
		i++;
	}
	free(cmds);
	return (token_lst);
}
