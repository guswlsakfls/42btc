/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:23:14 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/30 17:01:15 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_int(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("err: %d\n", errno);
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

char	*ft_readline(char *status, t_list *env)
{
	char	*input;
	sig_t	sig;

	input = NULL;
	sig = (void *)-1;
	if (status == NULL)
	{
		sig = signal(SIGINT, ft_sig_int);
		printf("%p", sig);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[0;91m\033[1mnano$ \033[0m");
		if (errno == 4)
			set_exit_status(1, env);
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
