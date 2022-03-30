/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyze.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:54:28 by dha               #+#    #+#             */
/*   Updated: 2022/03/30 16:06:38 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// when need padding
// \033[1A\033[5C

static void	cntl_D(t_mini *mini)
{
	ft_termios_org(mini);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

t_list	*analyze(char *cmd, t_list *envs, t_mini *mini)
{
	t_list	*tokens;
	t_list	*plines;

	if (cmd == NULL)
		cntl_D(mini);
	add_history(cmd);
	tokens = tokenize(cmd, envs);
	plines = merge_token(tokens, envs);
	optimize(plines, envs);
	free(cmd);
	if (tokens)
		clear_tokens(&tokens);
	return (plines);
}
