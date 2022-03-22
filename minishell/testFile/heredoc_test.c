#include "minishell.h"

int	main()
{
	pid_t	pid;
	char	*input;
	int		pipe_fd[2];
	int		fd;

	fd = open("./temp1.txt", O_WRONLY, O_CREAT, O_APPEND, 0777);
	if (fd < 0)
		exit(1);
	printf("fd : %d\n", fd);
	close(fd);
	close(fd);
	close(fd);
	close(fd);
	close(fd);
	dup2(fd, STDOUT_FILENO);
	printf("fd : %d\n", fd);
	//if (pipe(pipe_fd) < 0)
	//	exit(1);
	//pid = fork();
	//if (pid < 0)
	//	exit(1);
	//if (pid > 0)
	//{
//		close(pipe_fd[1]);
//		dup2(pipe_fd[0], STDIN_FILENO);
//		waitpid(pid, NULL, 0);
//
//	}
//	else
//	{
		// while (1)
		// {
		// 	input = readline("> ");
		// 	if (!input)
		// 		exit(1);
		// 	if (strncmp(input, "end", strlen("end")) != 0)
		// 	{
		// 		write(fd, input, strlen(input));
		// 		write(fd, "\n", 1);
		// 	}
		// 	else
		// 	{
		// 		close(fd);
		// 		free(input);
		// 		break;
		// 	}
		// 	free(input);
		// }
		// exit(0);
//	}
	return (0);
}
