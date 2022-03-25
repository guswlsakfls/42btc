/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nanoshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:11:02 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/25 19:11:45 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_check_pipe(t_pline *pline)
{
    if (pline->is_pipe == ISPIPE)
        if (pipe(pline->pipe_fd) < 0)
            exit(0);
}

void    ft_fork(t_list *plines, t_pline *cur, t_list *env, char **envp)
{
    t_pline *prev;

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
    // 자식에서 pline->pipe_fd[0] 은 있으면 사용하고 닫음만 잘하자. 인에서 어차피 닫는다.
    if (cur->pid == 0)
        ft_child(cur, prev, env, envp);
}

void    ft_nanoshell(t_list *plines, t_list *env, char **envp)
{
    t_list *cur_plines;
    t_pline *pline;

    cur_plines = plines;
    ft_redirection(cur_plines); // 리스트를 순회하며 infile 과 outfile 나온 fd 를 plines 에 file_fd[2] 로 넣어 두고 사용.
    while (cur_plines)
    {
        pline = (t_pline *)cur_plines->content;
        ft_check_pipe(pline);                  // 파이프인지 체크, fork를 할지 말지 체크해야함. // ft_open_pipe() 는 여기에 들어가면 될 것 같음
        ft_fork(cur_plines, pline, env, envp); // if (is_pipe || is_not_built_in)
        // ft_close_pipe(); 현재 열린 파이프와 이전에 사용된 파이프를 close 해준다.
        // 자식 프로세스를 다 돌고 나올때 까지 부모는 기다려 준다.
        // if (pline->heredoc_fd[0] == pline->file_fd[0])
        // {
        // 	close(pline->heredoc_fd[0]);
        // 	close(pline->file_fd[0]);
        // }
        // if (pline->file_fd[0])
        // 	close(pline->file_fd[0]);
        cur_plines = cur_plines->next;
    }
    // close(pline->pipe_fd[0]);
    // close(pline->pipe_fd[1]);
    // ft_close_pipe() // 명령이 끝났으므로 열린 fd는 모두 close 해야 무한루프에 빠지지 않는다.
}