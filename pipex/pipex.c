/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:00:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/21 18:17:22 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_parent(char **av, char **envp)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(av[3], ' ');
	path = ft_get_path(cmds[0], envp);
	if (ft_check_slash(cmds[0]) == 0 && path == 0)
		ft_print_error(3);
	else if (path == 0)
	{
		free(path);
		path = cmds[0];
	}
	if (execve(path, cmds, envp) < 0)
		ft_print_error(4);
}

void	ft_child(char **av, char **envp)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(av[2], ' ');
	path = ft_get_path(cmds[0], envp);
	if (ft_check_slash(cmds[0]) == 0 && path == 0)
		ft_print_error(3);
	else if (path == 0)
	{
		free(path);
		path = cmds[0];
	}
	if (execve(path, cmds, envp) < 0)
		ft_print_error(4);
}

void	ft_parent_fd(int *pipe_fd, int *file_fd, char **av)
{
	file_fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd[1] < 0)
		ft_print_error(6);
	dup2(file_fd[1], STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
}

void	ft_child_fd(int *pipe_fd, int *file_fd, char **av)
{
	file_fd[0] = open(av[1], O_RDONLY);
	if (file_fd[0] < 0)
		ft_print_error(2);
	dup2(file_fd[0], STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	int		file_fd[2];
	pid_t	pid1;

	if (ac != 5)
		ft_print_error(7);
	if (pipe(pipe_fd) < 0)
		ft_print_error(0);
	pid1 = fork();
	if (pid1 < 0)
		ft_print_error(1);
	if (pid1 > 0)
	{
		if (waitpid(pid1, NULL, WNOHANG) < 0)
			ft_print_error(5);
		ft_parent_fd(pipe_fd, file_fd, av);
		ft_parent(av, envp);
	}
	else if (pid1 == 0)
	{
		ft_child_fd(pipe_fd, file_fd, av);
		ft_child(av, envp);
	}
	return (0);
}
