/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:32 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/30 01:58:38 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_stdin(t_pline *cur, t_pline *prev)
{
	if (cur->is_pipe == ISPIPE)
		close(cur->pipe_fd[0]);
	if (cur->file_fd[0] != 0)
	{
		if (dup2(cur->file_fd[0], STDIN_FILENO) < 0)
			exit(1);
		close(cur->file_fd[0]);
	}
	else if (prev && prev->is_pipe == ISPIPE)
	{
		if (dup2(prev->pipe_fd[0], STDIN_FILENO) < 0)
			exit(1);
		close(prev->pipe_fd[0]);
	}
}

void	ft_check_stdout(t_pline *cur)
{
	if (cur->file_fd[1] != 0)
	{
		if (dup2(cur->file_fd[1], STDOUT_FILENO) < 0)
			exit(1);
		close(cur->file_fd[1]);
		if (cur->is_pipe == ISPIPE)
			close(cur->pipe_fd[1]);
	}
	else if (cur->is_pipe == ISPIPE && cur->file_fd[1] == 0)
	{
		if (dup2(cur->pipe_fd[1], STDOUT_FILENO) < 0)
			exit(1);
		close(cur->pipe_fd[1]);
	}
}

void	ft_child(t_pline *cur, t_pline *prev, t_list *env)
{
	ft_check_stdin(cur, prev);
	ft_check_stdout(cur);
	if (ft_built_in(cur->cmds, env) == 0)
	{
		if (cur->is_pipe == ISPIPE || prev->is_pipe == ISPIPE)
			exit(1);
	}
	else 
		ft_execute(cur->cmds, env);
}

void	ft_parent_close(t_pline *cur, t_pline *prev)
{
	if (prev && prev->pipe_fd[0])
		close(prev->pipe_fd[0]);
	if (cur->is_pipe == ISPIPE)
		close(cur->pipe_fd[1]);
}

void	ft_parent(t_pline *cur, t_pline *prev)
{
	signal(SIGINT, ft_sig_child);
	signal(SIGQUIT, ft_sig_quit);
	ft_parent_close(cur, prev);
}
