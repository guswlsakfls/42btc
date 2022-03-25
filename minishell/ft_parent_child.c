/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:32 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/25 19:52:15 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_check_stdin(t_pline *cur, t_pline *prev)
{
    // 자식에서 안쓰는 파이프 닫음
    if (cur->is_pipe == ISPIPE)
        close(cur->pipe_fd[0]);
    // 현재 인파일이 있으면 사용
    if (cur->file_fd[0] != 0)
    {
        dup2(cur->file_fd[0], STDIN_FILENO);
        close(cur->file_fd[0]);
    }
    // 이전에 파이프이고 아웃파일 없으면 넘어온거 사용
    else if (prev && prev->is_pipe == ISPIPE && prev->file_fd[1] == 0)
    {
        dup2(prev->pipe_fd[0], STDIN_FILENO);
        close(prev->pipe_fd[0]);
    }
}

void ft_check_stdout(t_pline *cur)
{
    if (cur->file_fd[1] != 0)
    {
        dup2(cur->file_fd[1], STDOUT_FILENO);
        close(cur->file_fd[1]);
        if (cur->is_pipe == ISPIPE)
            close(cur->pipe_fd[1]); // 아웃파일이 있으니 아웃파이프 꼭 다 닫기
    }
    // 아웃파일 없고 파이프면
    else if (cur->is_pipe == ISPIPE && cur->file_fd[1] == 0)
    {
        dup2(cur->pipe_fd[1], STDOUT_FILENO);
        close(cur->pipe_fd[1]); // 이거 추가함
    }
}

void ft_child(t_pline *cur, t_pline *prev, t_list *env, char **envp)
{
    signal(SIGINT, ft_sig_int); // CTRL + C
    signal(SIGQUIT, ft_sig_quit);
    rl_catch_signals = 1; // 1이면 시그널 처리 출력
    ft_check_stdin(cur, prev);
    ft_check_stdout(cur);
    if (ft_built_in(cur->cmds, env) == false)
        ft_execute(cur->cmds, env, envp);
}

void ft_parent_close(t_list *plines, t_pline *cur, t_pline *prev)
{
    if (prev && prev->pipe_fd[0]) // 이전 파이프 남아 있으면 닫자
        close(prev->pipe_fd[0]);
    if (cur->is_pipe == ISPIPE) // 여기 무한 루프 생겼음, 파이프 닫을 필요 없는데 닫아서 생김 슈발
        close(cur->pipe_fd[1]);
    if (cur->is_pipe == ISPIPE && plines->next == NULL) // 이거는 지금 파이프 인데 다음 커맨드 없으면 인듯?
        close(cur->pipe_fd[0]);
}

void ft_parent(t_list *plines, t_pline *cur, t_pline *prev)
{
    signal(SIGQUIT, SIG_IGN);
    waitpid(cur->pid, NULL, WUNTRACED); // WUNTRACED
    ft_parent_close(plines, cur, prev);
}