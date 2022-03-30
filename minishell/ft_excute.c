/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:13:15 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/30 13:19:01 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_execve(char **cmds)
{
	if (errno == 13)
		return (ft_error_print(cmds[0], "is a directory", 126));
	else if (ft_strchr(cmds[0], '/'))
		return (ft_error_print(cmds[0],
				"No such file or directory", 127));
	else if (errno == 2)
		return (ft_error_print(cmds[0], "command not found", 127));
	else
	{
		perror("nano");
		exit(errno);
	}
}

void	ft_execute(char **cmds, t_list *env)
{
	char	*path;
	int		exit_status;

	exit_status = 1;
	if ((ft_strnstr(cmds[0], "/minishell", ft_strlen(cmds[0]))))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		path = cmds[0];
	}
	if ((cmds[0][0] == '.' && cmds[0][1] == '/' ) || cmds[0][0] == '/')
		path = cmds[0];
	else
		path = (ft_get_envp(cmds[0], env, "PATH"));
	if (execve(path, cmds, ft_join_env(env)) < 0)
	{
		exit_status = ft_error_execve(cmds);
		exit(exit_status);
	}
}
