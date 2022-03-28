/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nanoshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:11:02 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/28 21:18:13 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_pipe(t_pline *pline)
{
	if (pline->is_pipe == ISPIPE)
	{
		if (pipe(pline->pipe_fd) < 0)
			exit(0);
	}
}

void	ft_fork(t_list *plines, t_pline *cur, t_list *env, char **envp)
{
	t_pline	*prev;

	if (plines->prev)
		prev = ((t_pline *)plines->prev->content);
	cur->pid = 0;
	if (cur->is_pipe == ISPIPE || ft_check_built_in(cur->cmds[0]) == false)
		cur->pid = fork();
	if (cur->pid < 0)
		exit(0);
	if (cur->pid > 0)
		ft_parent(cur, prev);
	if (cur->pid == 0)
		ft_child(cur, prev, env, envp);
}

void	ft_check_cmds_null(t_pline *cur, t_list *plines)
{
	t_pline	*prev;

	if (plines->prev)
		prev = ((t_pline *)plines->prev->content);
	if (cur->file_fd[0] != 0)
		close(cur->file_fd[0]);
	else if (prev && prev->is_pipe == ISPIPE && prev->file_fd[1] == 0)
		close(prev->pipe_fd[0]);
}

void	ft_close_fd(t_list *plines)
{
	t_pline	*pline;

	while (plines)
	{
		pline = (t_pline *)plines->content;
		if (pline->heredoc_fd[0] != 0)
			close(pline->heredoc_fd[0]);
		if (pline->file_fd[0] != 0)
			close(pline->file_fd[0]);
		if (pline->file_fd[1] != 0)
			close(pline->file_fd[1]);
		plines = plines->next;
	}
}

void	ft_nanoshell(t_list *plines, t_list *env, char **envp, t_mini *mini)
{
	t_list	*cur_plines;
	t_pline	*pline;

	cur_plines = plines;
	ft_redirection(cur_plines, mini);
	if (mini->statlog == 256)
	{
		ft_close_fd(cur_plines);
		mini->statlog = 0;
		return ;
	}
	// ft_termios_org(mini);
	while (cur_plines)
	{
		pline = (t_pline *)cur_plines->content;
		if (pline->cmds == NULL || pline->cmds[0] == NULL)
			ft_check_cmds_null(pline, cur_plines);
		else
		{
			ft_check_pipe(pline);
			ft_fork(cur_plines, pline, env, envp);
		}
		cur_plines = cur_plines->next;
	}
}
