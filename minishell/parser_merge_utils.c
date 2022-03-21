/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_merge_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:13:27 by dha               #+#    #+#             */
/*   Updated: 2022/03/20 22:32:12 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_type(t_list *token)
{
	return (((t_token *)token->content)->type);
}

t_token *token_dup(t_token *token)
{
	t_token *new;

	new = ft_malloc(sizeof(t_token), 1);
	new->type = token->type;
	new->str = ft_strdup(token->str);
	return (new);
}

void ft_stradd(t_pline *pline, int *idx, char *new)
{
	// if (new)
	// 	printf("idx: %d %s\n", *idx, new);
	if (pline->cnt == *idx)
	{
		pline->cmds = (char **)ft_realloc(pline->cmds, sizeof(char *) * pline->cnt, sizeof(char *) * pline->cnt * 2);
		pline->cnt = pline->cnt * 2;
	}
	pline->cmds[(*idx)++] = ft_strdup(new);
	if (!new)
	{
		pline->cmds = (char **)ft_realloc(pline->cmds, sizeof(char *) * *idx, sizeof(char *) * pline->cnt);
		*idx = pline->cnt;
		return;
	}
}