/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:20:57 by dha               #+#    #+#             */
/*   Updated: 2022/03/29 19:34:52 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char **argv, char *tmp, t_list **envs)
{
	int		ch_flag;

	if (!argv[1] || !ft_strncmp(argv[1], "#", 0) || \
		!ft_strncmp(argv[1], "~", 0))
	{
		tmp = env_value("HOME", *envs);
		if (tmp[0] == '\0')
			return (error_env_not_set(argv[0], ERR_HNS));
		ch_flag = chdir(tmp);
	}
	else if (!ft_strncmp(argv[1], "-", 0))
	{
		tmp = env_value("OLDPWD", *envs);
		if (tmp[0] == '\0')
			return (error_env_not_set(argv[0], ERR_ONS));
		ch_flag = chdir(tmp);
	}
	else
		ch_flag = chdir(argv[1]);
	if (ch_flag == -1)
	{
		perror("nano: cd");
		return (1);
	}
	return (0);
}

int	update_pwds(char **cwd, t_list **envs)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", *cwd);
	export_arg(tmp, envs);
	free(*cwd);
	free(tmp);
	*cwd = getcwd(NULL, 1024);
	if (*cwd == NULL)
	{
		perror("nano: cd");
		return (1);
	}
	tmp = ft_strjoin("PWD=", *cwd);
	export_arg(tmp, envs);
	free(*cwd);
	free(tmp);
	return (0);
}

int	builtin_cd(char **argv, t_list **envs)
{
	char	*cwd;
	char	*tmp;

	tmp = NULL;
	cwd = getcwd(NULL, 1024);
	if (cwd == NULL)
	{
		perror("nano: cd");
		return (1);
	}
	if (change_dir(argv, tmp, envs))
	{
		free(cwd);
		return (1);
	}
	if (update_pwds(&cwd, envs))
		return (1);
	return (0);
}
