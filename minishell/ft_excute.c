/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:13:15 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/29 22:26:16 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char **cmds, t_list *env, char **envp)
{
	char	*path;
	char	**temp;

	temp = envp;
	if ((cmds[0][0] == '.' && cmds[0][1] == '/' ) || cmds[0][0] == '/')
		path = cmds[0];
	else
		path = (ft_get_envp(cmds[0], env, "PATH"));
	if (execve(path, cmds, ft_join_env(env)) < 0)
	{
		// error 상황 보안해야함.
		perror("nano");
		exit(1);
	}
}
// printf("bash : %s: No such file or directory\n", cmds[0]);
