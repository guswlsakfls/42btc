/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:52:25 by dha               #+#    #+#             */
/*   Updated: 2022/03/20 22:33:40 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_redir(t_pline *pline, t_list **token, int type)
{
	t_list *next;

	next = (*token)->next;
	if (!next || !(get_type(next) & 1))
	{
		printf("syntax error redir\n");
		return (-1);
	}
	((t_token *)next->content)->type = get_type(*token);
	if (type & IREDIR || type & APPEND)
		ft_lstadd_back(&(pline->ifile), ft_lstnew(token_dup(next->content)));
	else
		ft_lstadd_back(&(pline->ofile), ft_lstnew(token_dup(next->content)));
	*token = next;
	return (0);
}

int parse_cmds(t_list **plines, t_cursor *cur, t_list *token)
{
	int i;
	int type;
	t_pline *pline;

	i = 0;
	pline = ft_malloc(sizeof(t_pline), 1);
	pline->cmds = ft_malloc(sizeof(char *), 4);
	pline->cnt = 4;
	if (cur->start == token || (token && token->next && get_type(token->next) & 2))
	{
		printf("Syntax error\n");
		return (-1);
	}
	while (cur->start != token)
	{
		type = get_type(cur->start);
		if (type & IREDIR || type & APPEND || type & OREDIR || type & HEREDOC)
		{
			if (parse_redir(pline, &(cur->start), type) == -1)
				return (-1);
		}
		else
			ft_stradd(pline, &i, ((t_token *)cur->start->content)->str);
		cur->start = cur->start->next;
	}
	ft_stradd(pline, &i, NULL);
	if (token != NULL)
		pline->is_pipe |= 1;
	ft_lstadd_back(plines, ft_lstnew(pline));
	return (0);
}

t_list *merge_token(t_list *tokens)
{
	t_list *plines;
	t_cursor *cur;
	// int type;

	plines = NULL;
	cur = ft_malloc(sizeof(t_cursor), 1);
	cur->start = tokens;
	while (tokens)
	{
		if (get_type(tokens) & PIPE)
		{
			if (parse_cmds(&plines, cur, tokens) == -1)
				return (NULL);
			cur->start = cur->start->next;
		}
		tokens = tokens->next;
	}
	if (parse_cmds(&plines, cur, 0) == -1)
		return (NULL);
	free(cur);
	return (plines);
}