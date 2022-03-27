/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:23:14 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/27 21:25:39 by hyujo            ###   ########.fr       */
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
	// rl_on_new_line();
	// rl_replace_line("", 1);
	// rl_redisplay(); // 이거 없애면 컨트롤 씨 했을 때 두번 출력 사라짐.
	exit(1);        // 히어독일때
}

void	ft_signal_normal()
{
	signal(SIGINT, ft_sig_int); // CTRL + C
	signal(SIGQUIT, SIG_IGN); // 평소 그리고 히어독은 그냥 무시하기 위해
}

void	ft_signal_heredoc()
{
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

	input = NULL;
	if (status == NULL)
	{
		ft_signal_normal();
		input = readline("\033[0;91m\033[1mdha's Prompt$ \033[0m");
	}
	else if (ft_strncmp("heredoc", status, 7) == 0)
	{
		ft_signal_heredoc();
		input = readline("> ");
	}
	ft_reset_signal();
	return (input);
}
