/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:18:53 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/01 14:36:44 by hyujo            ###   ########.fr       */
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

int	ft_check_file(t_pline *cur)
{
	if (ft_check_built_in(cur->cmds[0]) == 0 && cur->is_pipe != ISPIPE)
	{
		if (cur->file_fd[0] < 0 || cur->file_fd[1] < 0)
			return (1);
	}
	return (0);
}

void	ft_backup_pid(int *backup_pid)
{
	backup_pid[0] = dup(STDIN_FILENO);
	backup_pid[1] = dup(STDOUT_FILENO);
}

int	ft_check_statlog(t_mini *mini, t_list *cur_plines, t_list *env, int status)
{
	if (mini->statlog == 256)
	{
		ft_close_fd(cur_plines);
		set_exit_status(mini->statlog / 256, env);
		mini->statlog = 0;
		return (0);
	}
	else if (status == 1)
	{
		ft_close_fd(cur_plines);
		set_exit_status(1, env);
		mini->statlog = 0;
		return (0);
	}
	return (1);
}

void	ft_waitpid(t_list *cur_plines, t_mini *mini, t_list *env, int status)
{
	t_pline	*pline;
	int		statlog;

	mini->statlog = 0;
	statlog = status * 256;
	while (cur_plines && !status)
	{
		pline = (t_pline *)cur_plines->content;
		if (pline->pid > 0)
			waitpid(pline->pid, &statlog, WUNTRACED);
		statlog = ft_check_stat_env(statlog);
		if (((t_pline *)cur_plines->content)->file_fd[0] < 0)
			statlog = 256;
		cur_plines = cur_plines->next;
	}
	set_exit_status(statlog / 256, env);
}
