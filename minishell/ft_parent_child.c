/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:32 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/28 20:25:25 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_stdin(t_pline *cur, t_pline *prev)
{
	if (cur->is_pipe == ISPIPE)
		close(cur->pipe_fd[0]);
	if (cur->file_fd[0] != 0)
	{
		dup2(cur->file_fd[0], STDIN_FILENO);
		close(cur->file_fd[0]);
	}
	else if (prev && prev->is_pipe == ISPIPE)
	{
		dup2(prev->pipe_fd[0], STDIN_FILENO);
		close(prev->pipe_fd[0]);
	}
}

void	ft_check_stdout(t_pline *cur)
{
	if (cur->file_fd[1] != 0)
	{
		dup2(cur->file_fd[1], STDOUT_FILENO);
		close(cur->file_fd[1]);
		if (cur->is_pipe == ISPIPE)
			close(cur->pipe_fd[1]);
	}
	else if (cur->is_pipe == ISPIPE && cur->file_fd[1] == 0)
	{
		dup2(cur->pipe_fd[1], STDOUT_FILENO);
		close(cur->pipe_fd[1]);
	}
}

void	ft_child(t_pline *cur, t_pline *prev, t_list *env, char **envp)
{
	ft_check_stdin(cur, prev);
	ft_check_stdout(cur);
	if (ft_built_in(cur->cmds, env) == false)
		ft_execute(cur->cmds, env, envp);
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
	waitpid(cur->pid, NULL, WUNTRACED);
	ft_parent_close(cur, prev);
}
