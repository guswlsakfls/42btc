/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nanoshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:11:02 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/30 20:29:29 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork(t_list *plines, t_pline *cur, t_list *env, t_mini *mini)
{
	t_pline	*prev;
	int		backup_pid[2];
	int		status;

	status = 0;
	prev = NULL;
	if (plines->prev)
		prev = ((t_pline *)plines->prev->content);
	cur->pid = 0;
	ft_check_fork(cur, prev);
	ft_backup_pid(backup_pid);
	if (cur->pid == 0)
	{
		if (ft_check_file(cur) == 1)
			return (1);
		ft_termios_org(mini);
		status = ft_child(cur, prev, env);
	}
	ft_parent(cur, prev);
	if (dup2(backup_pid[0], STDIN_FILENO) < 0
		|| dup2(backup_pid[1], STDOUT_FILENO) < 0)
		exit(1);
	return (status);
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

int	ft_check_stat_env(int statlog)
{
	if (statlog == 2)
	{
		statlog = 130 * 256;
		ft_putstr_fd("\n", 1);
	}
	else if (statlog == 3)
	{
		statlog = 131 * 256;
		ft_putstr_fd("Quit: 3\n", 1);
	}
	return (statlog);
}

void	ft_nanoshell(t_list *plines, t_list *env, t_mini *mini)
{
	t_list	*cur_plines;
	t_pline	*pline;
	int		status;

	mini->statlog = 0;
	cur_plines = plines;
	status = ft_redirection(cur_plines, mini, env);
	if (ft_check_statlog(mini, cur_plines, env) == 0)
		return ;
	mini->statlog = status;
	while (cur_plines)
	{
		pline = (t_pline *)cur_plines->content;
		if (pline->cmds == NULL || pline->cmds[0] == NULL)
			ft_check_cmds_null(pline, cur_plines);
		else
		{
			ft_check_pipe(pline);
			status = ft_fork(cur_plines, pline, env, mini);
		}
		cur_plines = cur_plines->next;
	}
	cur_plines = plines;
	ft_waitpid(cur_plines, mini, env, status);
}
