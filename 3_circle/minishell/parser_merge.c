/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:52:25 by dha               #+#    #+#             */
/*   Updated: 2022/03/30 16:15:12 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redir(t_pline *pline, t_list **token, int type)
{
	t_list	*next;

	next = (*token)->next;
	if (!next || !(get_type(next) & 1))
	{
		if (!next)
			syntax_err_msg(0);
		else
			syntax_err_msg(get_type(next));
		return (-1);
	}
	((t_token *)next->content)->type = get_type(*token);
	if (type & IREDIR || type & HEREDOC)
		ft_lstadd_back(&(pline->ifile), ft_lstnew(token_dup(next->content)));
	else
		ft_lstadd_back(&(pline->ofile), ft_lstnew(token_dup(next->content)));
	*token = next;
	return (0);
}

int	parse_cmds(t_cursor *cur, t_list *token, t_pline *pline)
{
	int		idx;
	int		type;
	int		err_num;

	idx = 0;
	err_num = 0;
	while (cur->start != token)
	{
		type = get_type(cur->start);
		if (!(get_type(cur->start) & (CMD | PIPE)))
			err_num = parse_redir(pline, &(cur->start), type);
		else
			ft_stradd(pline, &idx, ((t_token *)cur->start->content)->str);
		if (err_num == -1)
			return (-1);
		cur->start = cur->start->next;
	}
	ft_stradd(pline, &idx, NULL);
	return (0);
}

int	store_cmds(t_list **plines, t_cursor *cur, t_list *token)
{
	int		err_num;
	t_pline	*pline;

	if (cur->start == token \
		|| (token && token->next && get_type(token->next) & PIPE))
	{
		syntax_err_msg(PIPE);
		return (-1);
	}
	pline = ft_malloc(sizeof(t_pline), 1);
	pline->cmds = ft_malloc(sizeof(char *), 4);
	pline->cnt = 4;
	err_num = parse_cmds(cur, token, pline);
	if (token != NULL)
		pline->is_pipe |= 1;
	ft_lstadd_back(plines, ft_lstnew(pline));
	if (err_num == -1)
		return (-1);
	return (0);
}

t_list	*merge_token(t_list *tokens, t_list *envs)
{
	t_list		*plines;
	t_cursor	*cur;

	if (tokens == NULL)
		return (NULL);
	plines = NULL;
	cur = ft_malloc(sizeof(t_cursor), 1);
	cur->start = tokens;
	while (tokens)
	{
		if (get_type(tokens) & PIPE)
		{
			if (store_cmds(&plines, cur, tokens) == -1)
				return (merge_err(&plines, cur, envs));
			cur->start = cur->start->next;
		}
		tokens = tokens->next;
	}
	if (store_cmds(&plines, cur, NULL) == -1)
		return (merge_err(&plines, cur, envs));
	free(cur);
	return (plines);
}
