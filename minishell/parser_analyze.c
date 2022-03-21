/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyze.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:54:28 by dha               #+#    #+#             */
/*   Updated: 2022/03/20 23:57:53 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *get_t(t_pline *pline, int i)
{
	if (i)
		return ((t_token *)pline->ifile->content);
	else
		return ((t_token *)pline->ofile->content);
}

t_list *analyze(char *cmd)
{
	t_list *tokens;
	t_list *plines;
	t_list *tmp;
	int i;

	printf("cmd: %s\n", cmd);
	if (cmd == NULL)   // input Ctrl + D in prompt
		return (NULL); // has to be fixed to exit bash
	tokens = tokenize(cmd);
	free(cmd);
	tmp = tokens;
	if (tokens == NULL)
		return (NULL);
	plines = merge_token(tokens);
	tokens_clear(&tokens);
	tokens = NULL;
	// system("leaks minishell");
	printf("-----------\n");
	tmp = plines;
	while (tmp)
	{
		i = 0;
		while (((t_pline *)tmp->content)->cmds[i])
		{
			printf("%d: %s\n", i, ((t_pline *)tmp->content)->cmds[i]);
			i++;
		}
		// while (((t_pline *)tmp->content)->ifile)
		// {
		// 	printf("%s ", get_t(tmp->content, 1)->str);
		// 	((t_pline *)tmp->content)->ifile = ((t_pline *)tmp->content)->ifile->next;
		// }
		// while (((t_pline *)tmp->content)->ofile)
		// {
		// 	printf("%s ", get_t(tmp->content, 0)->str);
		// 	((t_pline *)tmp->content)->ofile = ((t_pline *)tmp->content)->ofile->next;
		// }
		// printf("\n");
		tmp = tmp->next;
	}
	return (plines);
}