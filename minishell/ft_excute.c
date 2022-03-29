/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:13:15 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/30 02:27:02 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char **cmds, t_list *env)
{
	char	*path;

	if ((cmds[0][0] == '.' && cmds[0][1] == '/' ) || cmds[0][0] == '/')
		path = cmds[0];
	else
		path = (ft_get_envp(cmds[0], env, "PATH"));
	if (execve(path, cmds, ft_join_env(env)) < 0)
	{
		if (cmds[0][0] == '/' && cmds[0][1] == '\0')
			ft_error_print(cmds[0], "is a directory", 126);
		else if (cmds[0][0] == '/' || (cmds[0][0] == '.' && cmds[0][1] == '/'))
			ft_error_print(cmds[0], "No such file or directory", 127);
		else
			ft_error_print(cmds[0], "command not found", 127);
		// perror("nano");
		exit(1);
	}
}
// printf("bash : %s: No such file or directory\n", cmds[0]);
