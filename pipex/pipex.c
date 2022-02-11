/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:00:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/11 18:04:43 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int	main(int ac, char **av, char **envp)
{
	int	i;

	ac = 1;
	av = NULL;
	i = 0;
	while (envp[i])
	{
		printf("<%2d> : %s\n", i, envp[i]);
		i++;
	}
	return (0);
}
