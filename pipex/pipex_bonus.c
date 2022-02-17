/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:00:53 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/17 19:34:40 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"
#include <stdio.h>

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

int	ft_check_slash(char *cmds)
{
	if (ft_strncmp(cmds, "/", 1) == 0)
		return (1);
	else if (ft_strncmp(cmds, "./", 2) == 0)
		return (1);
	else if (ft_strncmp(cmds, "../", 3) == 0)
		return (1);
	return (0);
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
	}
	free(path_list);
	ft_free(paths);
	return (0);
}

void	ft_execute(char *av, char **envp)
{
	char	**cmds;
	char	*path;
	int		i;

	i = 0;
	cmds = ft_split(av, ' ');
	path = ft_get_path(cmds[0], envp);
	if (!path)
	{
		ft_free(cmds);
		ft_print_error(3);
	}
	if (execve(path, cmds, envp) < 0)
		ft_print_error(4);
}

void	ft_child_process(char	*av, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		ft_print_error(0);
	pid = fork();
	if (pid < 0)
		ft_print_error(1);
	if (pid > 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		ft_execute(av, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		pipe_fd[2];
	int		file_fd[2];
	pid_t	pid1;
	char	*line;
	char	buf[10000];

	i = 0;
	if (ac < 5)
		ft_print_error(7);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac != 6)
			ft_print_error(7);
		i = 3;
		file_fd[1] = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (pipe(pipe_fd) < 0)
			ft_print_error(0);
		pid1 = fork();
		if (pid1 < 0)
			ft_print_error(1);
		if (pid1 > 0)
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);
			waitpid(pid1, NULL, 0);
		}
		else
		{
			close(pipe_fd[0]);
			while (ft_get_next_line(&line))
			{
				if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
					exit(0);
				write(pipe_fd[1], line, ft_strlen(line));
				read(pipe_fd[1], buf, 1024);
				fprintf(stderr, "pipe_fd[1] : %s\n", buf);
			}
		}
	}
	else
	{
		i = 2;
		file_fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		file_fd[0] = open(av[1], O_RDONLY, 0777);
		dup2(file_fd[0], STDIN_FILENO);
	}
	while (i < ac - 2)
		ft_child_process(av[++i], envp);
	dup2(file_fd[1], STDOUT_FILENO);
	ft_execute(av[ac - 2], envp);
}
