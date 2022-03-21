/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:44:56 by dha               #+#    #+#             */
/*   Updated: 2022/03/20 19:32:15 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_symbol(char *cmd)
{
	if (!strncmp("<<", cmd, 2) || !strncmp(">>", cmd, 2))
		return (2);
	if (*cmd == '|' || *cmd == '<' || *cmd == '>')
		return (1);
	return (0);
}

int token_type(char *cmd)
{
	if (!strncmp("<<", cmd, 2))
		return (HEREDOC);
	if (!strncmp(">>", cmd, 2))
		return (APPEND);
	if (*cmd == '<')
		return (IREDIR);
	if (*cmd == '>')
		return (OREDIR);
	if (*cmd == '|')
		return (PIPE);
	return (CMD);
}

void token_clear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	if (lst == 0)
		return;
	while (*lst)
	{
		tmp = *lst;
		del(((t_token *)(*lst)->content)->str);
		*lst = tmp->next;
		ft_lstdelone(tmp, del);
	}
}