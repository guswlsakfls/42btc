/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:13:15 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/28 21:56:53 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char **cmds, t_list *env, char **envp)
{
	char	*path;
	char	**temp;

	temp = envp;
	if (cmds[0][0] == '/')
		path = cmds[0];
	else
		path = (ft_get_envp(cmds[0], env, "PATH"));
	if (execve(path, cmds, ft_join_env(env)) < 0)
	{
		// error 상황 보안해야함.
		if (path[0] == '/' && path[1] != '\0')
			printf("bash : %s: No such file or directory\n", cmds[0]);
		else if (path == NULL)
			printf("bash : %s: command not found\n", cmds[0]);
		else
			printf("bash : /: is a directory\n");
		exit(1);
	}
}
