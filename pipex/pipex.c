/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:00:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/15 19:46:48 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_print_error(int num)
{
	if (num == 0)
		ft_putstr_fd("pipe error\n", 2);
	else if (num == 1)
		ft_putstr_fd("fork error\n", 2);
	else if (num == 2)
		ft_putstr_fd("infile error\n", 2);
	else if (num == 3)
		ft_putstr_fd("access error\n", 2);
	else if (num == 4)
		ft_putstr_fd("execve error\n", 2);
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
	paths = ft_split(envp[i], ':');
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
	}
	free(path_list);
	ft_free(paths);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		pipe_fd[2];
	int		file_fd[2];
	char	**cmds;
	pid_t	pid1;
	char	*path;

	i = 0;
	if (ac < 5)
		return (0);
	if (pipe(pipe_fd) < 0)
		ft_print_error(0);
	pid1 = fork();
	if (pid1 < 0)
		ft_print_error(1);
	if (pid1 > 0)
	{
		waitpid(pid1, NULL, 0);
		file_fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(file_fd[1], STDOUT_FILENO);
		dup2(pipe_fd[WRITE], STDIN_FILENO);
		close(pipe_fd[READ]);
		cmds = ft_split(av[3], ' ');
		path = ft_get_path(cmds[0], envp);
		if (path == 0)
			ft_print_error(3);
		if (execve(path, cmds, envp) < 0)
			ft_print_error(4);
	}
	else if (pid1 == 0)
	{
		file_fd[0] = open(av[1], O_RDONLY);
		if (file_fd[0] < 0)
			ft_print_error(2);
		dup2(file_fd[0], STDIN_FILENO);
		dup2(pipe_fd[READ], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		cmds = ft_split(av[2], ' ');
		path = ft_get_path(cmds[0], envp);
		if (path == 0)
			ft_print_error(3);
		if (execve(path, cmds, envp) < 0)
			ft_print_error(4);
	}
	return (0);
}
