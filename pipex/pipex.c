/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:00:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/14 19:55:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// int	ft_parse_cmd(char **argv, char **envp)
// {

// }

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
	exit(1);
}

void	ft_free_cmds(char **cmds)
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

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		pipe_fd[2];
	int		file_fd[2];
	char	**cmds;
	pid_t	pid1;

	i = 0;
	if (ac < 5)
		return (0);
	if (pipe(pipe_fd) < 0)
		ft_print_error(0);
	pid1 = fork();
	if (pid1 < 0)
		ft_print_error(1);
	// 부모 프로세스
	if (pid1 > 0)
	{
		waitpid(pid1, NULL, 0);
		file_fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		printf("부모\n");
		cmds = ft_split(av[3], ' ');
		dup2(file_fd[1], 1); // 1 은 파일에 쓴다.
		dup2(pipe_fd[WRITE], WRITE);
		close(pipe_fd[READ]);
		execve("usr/bin/wc", cmds, envp);
	}
	// 자식 프로세스
	else if (pid1 == 0)
	{
		printf("자식\n");
		if (access(av[1], F_OK))
			ft_print_error(3);
		file_fd[0] = open(av[1], O_RDONLY);
		if (file_fd[0] < 0)
			ft_print_error(2);
		dup2(file_fd[0], 0); // 0 은 파일 안에 내용을 읽어온다.
		dup2(pipe_fd[READ], READ); // 자식은 파일을 읽어와 커맨드로 데이터를 파이프에 쓴다.
		close(pipe_fd[WRITE]);
		cmds = ft_split(av[2], ' ');
		execve("/bin/ls", cmds, envp);
		ft_free_cmds(cmds);
	}

	// ---------------printf------------------------------------------------------
	printf("__________envp__________\n");
	printf("%s\n", envp[3]);
	return (0);
}
