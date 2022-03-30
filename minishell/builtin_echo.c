/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:21:29 by dha               #+#    #+#             */
/*   Updated: 2022/03/30 09:35:33 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_flag(char **argv, int *idx, int *flag)
{
	while (argv[++idx[0]][0] == '-')
	{
		idx[1] = 0;
		while (argv[idx[0]][++idx[1]])
		{
			if (argv[idx[0]][idx[1]] != 'n')
				break ;
		}
		if (argv[idx[0]][idx[1]])
			break ;
		*flag |= 1;
	}
}

int	builtin_echo(char **argv, t_list **envs)
{
	int	*idx;
	int	flag;

	(void) envs;
	if (argv[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	idx = ft_malloc(sizeof(int), 2);
	flag = 0;
	check_flag(argv, idx, &flag);
	while (argv[idx[0]])
	{
		ft_putstr_fd(argv[idx[0]], 1);
		if (argv[idx[0] + 1])
			write(1, " ", 1);
		idx[0]++;
	}
	if (!flag)
		write(1, "\n", 1);
	free(idx);
	return (0);
}
