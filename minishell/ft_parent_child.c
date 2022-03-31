/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:32 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/31 17:42:18 by hyujo            ###   ########.fr       */
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

int	ft_child(t_pline *cur, t_pline *prev, t_list *env)
{
	int	status;

	ft_check_stdin(cur, prev);
	ft_check_stdout(cur);
	status = ft_built_in(cur->cmds, env);
	if (status == 0 || status == 1)
	{
		if (cur->is_pipe == ISPIPE || (prev && prev->is_pipe == ISPIPE))
			exit(1);
		return (status);
	}
	else
		ft_execute(cur->cmds, env);
	return (0);
}

void	ft_parent_close(t_pline *cur, t_pline *prev)
{
	if (prev && prev->pipe_fd[0])
		close(prev->pipe_fd[0]);
	if (cur->is_pipe == ISPIPE)
		close(cur->pipe_fd[1]);
	if (cur->file_fd[0] > 0)
		close(cur->file_fd[0]);
	if (cur->file_fd[1] > 0)
		close(cur->file_fd[1]);
}

void	ft_parent(t_pline *cur, t_pline *prev)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_parent_close(cur, prev);
}
