/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/27 19:17:22 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (argc > 2)
		exit(1);
	if (argv[0] == NULL)
		exit(1);
	// 처음에 envp 초기화 해서 가지고 다녀야 한다.
	printf("\n\nNANOSHELL BY HYUJO & DHA\n\n");
	env = ft_init_envs(envp);
	rl_catch_signals = 0; // 0이면 시그널 처리 출력 x
	while (1)
	{
		plines = analyze(ft_readline(NULL), env);
		ft_nanoshell(plines, env, envp);
		// system("leaks minishell");
		free(plines);
	}
	return (0);
}
