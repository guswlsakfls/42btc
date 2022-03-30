/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:23:14 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/30 16:33:26 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_int(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ft_sig_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	exit(0);
}

char	*ft_readline(char *status)
{
	char	*input;

	input = NULL;
	if (status == NULL)
	{
		signal(SIGINT, ft_sig_int);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[0;91m\033[1mnano$ \033[0m");
	}
	else if (ft_strncmp("heredoc", status, 7) == 0)
	{
		signal(SIGINT, ft_sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
		input = readline("> ");
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (input);
}
