/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/30 16:27:57 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_termios_org(t_mini *mini)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(mini->org_term));
}

void	ft_termios_echoctl(t_mini *mini)
{
	tcgetattr(STDIN_FILENO, &(mini->org_term));
	mini->new_term = mini->org_term;
	mini->new_term.c_lflag &= ~ECHOCTL;
}

void	ft_termios_new(t_mini *mini)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(mini->new_term));
}

void	ft_free_two(char ***split)
{
	int	i;

	i = 0;
	if (*split == NULL)
		return ;
	while ((*split)[i] != NULL)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*plines;
	t_list	*env;
	t_mini	*mini;

	if (argc > 2)
		exit(1);
	if (argv[0] == NULL)
		exit(1);
	printf("\n\nNANOSHELL BY HYUJO & DHA\n\n");
	env = ft_init_envs(envp);
	mini = malloc(sizeof(t_mini));
	ft_termios_echoctl(mini);
	while (1)
	{
		ft_termios_new(mini);
		plines = analyze(ft_readline(NULL), env, mini);
		if (plines == NULL)
			continue ;
		ft_nanoshell(plines, env, mini);
		ft_lstclear(&plines, clear_pline);
	}
	return (0);
}
