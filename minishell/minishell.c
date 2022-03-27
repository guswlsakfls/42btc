/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/28 01:54:46 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_termios_echoctl(t_mini *mini)
{
	tcgetattr(STDIN_FILENO, &(mini->org_term));
	tcgetattr(STDIN_FILENO, &(mini->new_term));
	// mini->new_term.c_lflag &= ~ISIG; // off하면 반향되지않는다. 즉 입력받지 않음 abc입력해도 안뜸
	mini->new_term.c_lflag &= ~ECHOCTL;
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

int main(int argc, char ** argv, char** envp) //  int argc, char **argv, char **envp
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
	while (1)
	{
		ft_termios_echoctl(mini);
		plines = analyze(ft_readline(NULL), env);
		ft_nanoshell(plines, env, envp, mini);
		// system("leaks minishell");
		free(plines);
	}
	free(mini);
	return (0);
}
