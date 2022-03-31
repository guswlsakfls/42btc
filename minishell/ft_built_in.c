/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:32:42 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/31 09:27:31 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_in(char **cmds, t_list *env)
{
	if ((ft_strncmp(cmds[0], "echo", 0)) == 0)
		builtin_echo(cmds, &env);
	else if ((ft_strncmp(cmds[0], "cd", 0)) == 0)
		builtin_cd(cmds, &env);
	else if ((ft_strncmp(cmds[0], "pwd", 0)) == 0)
		builtin_pwd(cmds, &env);
	else if ((ft_strncmp(cmds[0], "env", 0)) == 0)
		builtin_env(cmds, &env);
	else if ((ft_strncmp(cmds[0], "export", 0)) == 0)
		builtin_export(cmds, &env);
	else if ((ft_strncmp(cmds[0], "unset", 0)) == 0)
		builtin_unset(cmds, &env);
	else if ((ft_strncmp(cmds[0], "exit", 0)) == 0)
		builtin_exit(cmds, &env);
	else
		return (1);
	return (0);
}

int	ft_check_built_in(char *cmd)
{
	if ((ft_strncmp(cmd, "echo", 0)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "cd", 0)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "pwd", 0)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "env", 0)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "export", 0)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "unset", 0)) == 0)
		return (0);
	else if ((ft_strncmp(cmd, "exit", 0)) == 0)
		return (0);
	return (1);
}
