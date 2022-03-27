/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nanoshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:11:02 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/28 02:23:25 by hyunjinjo        ###   ########.fr       */
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
    // 포크할 필요가 없으면 pid == 0 으로 들어가 처리 한다.
	cur->pid = 0;
	if (cur->is_pipe == ISPIPE || ft_check_built_in(cur->cmds[0]) == false) // fork 는 파이프가 있거나 execve 를 쓰거나 할 때 분기 한다.
		cur->pid = fork();
	if (cur->pid < 0)
		exit(0);
	if (cur->pid > 0)
		ft_parent(plines, cur, prev);
    // 자식에서 pline->pipe_fd[0] 은 있으면 사용하고 닫음만 잘하자. 안에서 어차피 닫는다.
	if (cur->pid == 0)
		ft_child(cur, prev, env, envp);
}

void ft_check_cmds_null(t_pline *cur, t_list *plines)
{
	t_pline	*prev;

	if (plines->prev)
		prev = ((t_pline *)plines->prev->content);
	if (cur->heredoc_fd[0])
		close(cur->heredoc_fd[0]);
	if (cur->file_fd[0] != 0)
		close(cur->file_fd[0]);
	else if (prev && prev->is_pipe == ISPIPE && prev->file_fd[1] == 0)
		close(prev->pipe_fd[0]);
}

	void ft_nanoshell(t_list *plines, t_list *env, char **envp, t_mini *mini)
{
	t_list	*cur_plines;
	t_pline	*pline;

	cur_plines = plines;
	ft_redirection(cur_plines, mini);
	while (cur_plines)
	{
		pline = (t_pline *)cur_plines->content;
		if (mini->statlog == 256) // 히어독 ctrl+c 일 때
		{
			if (pline->heredoc_fd[0] != 0)
				close(pline->heredoc_fd[0]);
		}
		else if (pline->cmds == NULL || pline->cmds[0] == NULL) // cmds 가 없으면 파일 체크하고 그냥 출력없이 지나가야함.
			ft_check_cmds_null(pline, cur_plines);
		else
		{
			ft_check_pipe(pline);
			ft_fork(cur_plines, pline, env, envp);
		}
		cur_plines = cur_plines->next;
	}
}
