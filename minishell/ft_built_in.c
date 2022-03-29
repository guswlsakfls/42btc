/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:32:42 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/29 19:07:52 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_in(char **cmds, t_list *env)
{
	t_list	*list;

	list = env;
	printf("%s\n", *cmds);
	// if ((ft_strncmp(cmds[0], "echo", 5)) == 0)
	// 	builtin_echo(cmds, &env);
	// else if ((ft_strncmp(cmds[0], "cd", 3)) == 0)
	// 	bulitin_cd(cmds, &env);
	// else if ((ft_strncmp(cmds[0], "pwd", 4)) == 0)
	// 	bulitin_pwd(cmds, &env);
	// else if ((ft_strncmp(cmds[0], "env", 4)) == 0)
	// 	bulitin_env(cmds, &env);
	// else if ((ft_strncmp(cmds[0], "export", 7)) == 0)
	// 	bulitin_export(cmds, &env);
	// else if ((ft_strncmp(cmds[0], "unset", 6)) == 0)
	// 	builtin_unset(cmds, &env);
	// else if ((ft_strncmp(cmds[0], "exit", 5)) == 0)
	// 	builtin_exit(cmds, &env);
	// else
		return (0);
	// return (1);
}

int	ft_check_built_in(char *cmd)
{
	if ((ft_strncmp(cmd, "echo", 5)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "cd", 3)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "pwd", 4)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "env", 4)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "export", 7)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "unset", 6)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "exit", 5)) == 0)
		return (0);
	return (1);
}
