#include "minishell.h"

int	main()
{
	pid_t	pid;
	char	*input;
	int		pipe_fd[2];
	char	buf[100];
	int		ret;

	ret = 10;
	if (pipe(pipe_fd) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
	{
		ret = (int)signal(SIGINT, SIG_IGN);
		printf("ret : %d\n", ret);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	else if (pid == 0)
	{
		while (1)
		{
			input = readline("> ");
			if (!input)
				exit(1);
			if (strncmp(input, "end", strlen("end")) != 0)
			{
				write(pipe_fd[1], input, strlen(input));
				write(pipe_fd[1], "\n", 1);
			}
			else
			{
				close(pipe_fd[1]);
				free(input);
				break;
			}
			free(input);
		}
		exit(0);
	}
	read(pipe_fd[0], buf, 100);
	printf("buf : %s", buf);
	return (0);
}
