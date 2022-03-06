/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:02:18 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/22 11:24:51 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

int	ft_get_next_line(char **line)
{
	char	save[999999];
	char	buff[1];
	int		i;

	i = -1;
	save[i] = '\0';
	while (read(0, buff, 1) == 1)
	{
		save[++i] = buff[0];
		save[i + 1] = '\0';
		if (save[i] == '\n')
			break ;
	}
	if (save[0] == '\0')
		return (0);
	(*line) = malloc(i + 1);
	i = -1;
	while (save[++i])
		(*line)[i] = save[i];
	(*line)[i] = '\0';
	return (1);
}

void	ft_print_error(int num)
{
	if (num == 0)
		ft_putstr_fd("pipe error\n", 2);
	else if (num == 1)
		ft_putstr_fd("fork error\n", 2);
	else if (num == 2)
		ft_putstr_fd("infile error\n", 2);
	else if (num == 3)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	else if (num == 4)
		ft_putstr_fd("execve error\n", 2);
	else if (num == 5)
		ft_putstr_fd("waitpid error\n", 2);
	else if (num == 6)
		ft_putstr_fd("outfile error\n", 2);
	else if (num == 7)
		ft_putstr_fd("argument error\n", 2);
	exit(1);
}

void	ft_free(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path_list;
	char	*path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		path_list = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_list, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free(paths);
			free(path_list);
			return (path);
		}
		free(path);
		free(path_list);
	}
	ft_free(paths);
	return (0);
}
