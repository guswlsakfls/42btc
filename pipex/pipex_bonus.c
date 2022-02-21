/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:00:53 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/21 15:22:23 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

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
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_execute(av, envp);
	}
}

void	ft_here_doc(char **av)
{
	pid_t	pid1;
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		ft_print_error(0);
	pid1 = fork();
	if (pid1 < 0)
		ft_print_error(1);
	if (pid1 > 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		wait(NULL);
	}
	else
	{
		close(pipe_fd[0]);
		while (ft_get_next_line(&line))
		{
			if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
				exit(0);
			write(pipe_fd[1], line, ft_strlen(line));
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		file_fd[2];

	i = 0;
	if (ac < 5)
		ft_print_error(7);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac != 6)
			ft_print_error(7);
		i = 2;
		file_fd[1] = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0777);
		ft_here_doc(av);
	}
	else
	{
		i = 1;
		file_fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		file_fd[0] = open(av[1], O_RDONLY, 0777);
		dup2(file_fd[0], STDIN_FILENO);
	}
	while (i < ac - 2)
		ft_child_process(av[++i], envp);
	dup2(file_fd[1], STDOUT_FILENO);
	ft_execute(av[ac - 2], envp);
}
