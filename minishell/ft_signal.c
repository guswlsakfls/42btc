/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:23:14 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/26 19:28:04 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_quit(int signum)
{
	if (signum != SIGQUIT)
		return;
	printf("Quit: 3\n");
}

void	ft_sig_int(int signum)
{
	if (signum != SIGINT)
		return;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay(); // 이거 없애면 컨트롤 씨 했을 때 두번 출력 사라짐.
}

void	ft_sig_heredoc(int signum)
{
	if (signum != SIGINT)
		return;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	// rl_redisplay(); // 이거 없애면 컨트롤 씨 했을 때 두번 출력 사라짐.
	exit(1);        // 히어독일때
}

void	ft_signal_ign()
{
	signal(SIGINT, SIG_IGN); // CTRL + C
	signal(SIGQUIT, SIG_IGN);   // 평소 그리고 히어독은 그냥 무시하기 위해
}

void	ft_signal_normal()
{
    // if (평소)
	signal(SIGINT, ft_sig_int); // CTRL + C
	signal(SIGQUIT, SIG_IGN); // 평소 그리고 히어독은 그냥 무시하기 위해
}

void	ft_signal_heredoc()
{
    // if (평소)
	signal(SIGINT, ft_sig_heredoc); // CTRL + C
	signal(SIGQUIT, SIG_IGN); // 평소 그리고 히어독은 그냥 무시하기 위해

}

void	ft_reset_signal()
{
	signal(SIGINT, SIG_DFL); // CTRL + C
	signal(SIGQUIT, SIG_DFL); // 평소 그리고 히어독은 그냥 무시하기 위해
}

char	*ft_readline(char *status)
{
	char	*input;

    // 문자열을 안 넣을 때, 일반적인 프롬프트라는 뜻
	input = NULL;
	if (status == NULL)
	{
        // 일반 프롬프트 상황 시그널 처리
		ft_signal_normal();
		input = readline("\033[0;91m\033[1mdha's Prompt$ \033[0m");
	}
    // 문자열을 넣었을 때, 히어독 상태 리드라인
	else if (ft_strncmp("heredoc", status, 7) == 0) // 히어독 상태인 지 확인
	{
        // 히어독 상황 시그널 처리
		ft_signal_heredoc();
		input = readline("> ");
	}
    // 여기서 다시 기본 시그널 처리로 변환(이 안에서 signal(...)해서 처리방식 정하겠죠?)
	ft_reset_signal();
	return (input);
}
