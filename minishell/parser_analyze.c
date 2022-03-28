/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyze.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:54:28 by dha               #+#    #+#             */
/*   Updated: 2022/03/28 20:56:49 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cntl_D(t_mini *mini)
{
	ft_termios_org(mini);
	ft_putstr_fd("\x1b[1A", 1);
	ft_putstr_fd("\033[12C", 1);
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
	tokens = tokenize(cmd);
	plines = merge_token(tokens);
	optimize(plines, envs);
	free(cmd);
	if (tokens)
		clear_tokens(&tokens);
	// int		i;
	// t_list	*tmp;
	// t_list	*tmp_ifile;
	// t_list	*tmp_ofile;
	// tmp = plines;
	// while (tmp)
	// {
	// 	i = 0;
	// 	tmp_ifile = ((t_pline *)tmp->content)->ifile;
	// 	tmp_ofile = ((t_pline *)tmp->content)->ofile;
	// 	while (((t_pline *)tmp->content)->cmds[i])
	// 	{
	// 		if (ft_strncmp(((t_pline *)tmp->content)->cmds[i], "env", 0) == 0)
	// 			builtin_env(((t_pline *)tmp->content)->cmds, &envs);
	// 		if (ft_strncmp(((t_pline *)tmp->content)->cmds[i], "export", 0) == 0)
	// 			builtin_export(((t_pline *)tmp->content)->cmds, &envs);
	// 		if (ft_strncmp(((t_pline *)tmp->content)->cmds[i], "unset", 0) == 0)
	// 			builtin_unset(((t_pline *)tmp->content)->cmds, &envs);
	// 		i++;
	// 	}
	// 	while (tmp_ifile)
	// 	{
	// 		printf("i: %s ", ((t_token *)tmp_ifile->content)->str);
	// 		tmp_ifile = tmp_ifile->next;
	// 	}
	// 	while (tmp_ofile)
	// 	{
	// 		printf("o: %s ", ((t_token *)tmp_ofile->content)->str);
	// 		tmp_ofile = tmp_ofile->next;
	// 	}
	// 	printf("\n");
	// 	tmp = tmp->next;
	// }
	// system("leaks minishell");
	return (plines);
}
