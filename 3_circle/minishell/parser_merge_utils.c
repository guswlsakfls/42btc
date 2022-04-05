/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_merge_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:13:27 by dha               #+#    #+#             */
/*   Updated: 2022/03/30 16:21:02 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(t_list *token)
{
	return (((t_token *)token->content)->type);
}

t_token	*token_dup(t_token *token)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), 1);
	new->type = token->type;
	new->str = ft_strdup(token->str);
	return (new);
}

void	ft_stradd(t_pline *pline, int *idx, char *new)
{
	if (pline->cnt == *idx)
	{
		pline->cmds = (char **) ft_realloc(pline->cmds, sizeof(char *)
				* pline->cnt, sizeof(char *) * pline->cnt * 2);
		pline->cnt = pline->cnt * 2;
	}
	pline->cmds[(*idx)++] = ft_strdup(new);
	if (!new)
	{
		pline->cmds = (char **) ft_realloc(pline->cmds, sizeof(char *)
				* *idx, sizeof(char *) * pline->cnt);
		*idx = pline->cnt;
		return ;
	}
}

void	clear_pline(void *pline)
{
	ft_strarr_clear(&(((t_pline *)pline)->cmds));
	clear_tokens(&((t_pline *)pline)->ifile);
	clear_tokens(&((t_pline *)pline)->ofile);
	free(pline);
}

t_list	*merge_err(t_list **plines, t_cursor *cur, t_list *envs)
{
	set_exit_status(258, envs);
	ft_lstclear(plines, clear_pline);
	free(cur);
	*plines = NULL;
	return (NULL);
}
