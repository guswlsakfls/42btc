/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:00:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/12 19:35:53 by hyujo            ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		pipe_fd[2];
	int		infile_fd;
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
		printf("부모\n");
	}
	// 자식 프로세스
	else if (pid1 == 0)
	{
		printf("자식\n");
		if (access(av[1], F_OK))
			ft_print_error(3);
		infile_fd = open(av[1], O_RDONLY);
		if (infile_fd < 0)
			ft_print_error(2);
		dup2(infile_fd, 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		execve(av[2], ac, envp);
	}

	// ---------------printf------------------------------------------------------
	printf("__________envp__________\n");
	printf("%s\n", envp[3]);
	return (0);
}
