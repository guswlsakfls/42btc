#include "minishell.h"

void ft_child_heredoc(int *fd)
{
	char	*input;

	close(fd[0]);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("\x1b[1A", 1);
			ft_putstr_fd("\033[2C", 1);
			exit(0);
		}
		if (ft_strncmp(input, "a", 1) != 0)
		{
			ft_putstr_fd(input, fd[1]); // 계속 데이터가 fd 파일에 쌓인다.
			ft_putstr_fd("\n", fd[1]);
			free(input);
		}
		else
		{
			free(input);
			exit(0);
		}
	}
}

int main(void)
{
	pid_t	pid;
	int		fd[2];
	struct termios	org_term;
	struct termios	new_term;
	// tcgetattr(STDIN_FILENO, &org_term);
	// //c_lflag 안의 옵션들은 모두 on되어있는 상태이고 엔드연산자로 off를 시킨다.
	// // term.c_lflag &= ~ICANON; // 이 플래그가 on되어있으면 정규모드 off면 비정규모드이다.
	// // 정규모드 : 터미널 기본입력모드로 한줄씩 받는것이다. 비정규모드 : 한글자씩 받는것이다.
	// org_term.c_lflag &= ~ISIG; // off하면 반향되지않는다. 즉 입력받지 않음 abc입력해도 안뜸
	// // term.c_cc[VMIN] = 1; // 한글자를 받을때까지
	// // term.c_cc[VTIME] = 0; // 한무대기
	// tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
	if (pipe(fd) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
	{
		tcgetattr(STDIN_FILENO, &(org_term));
		tcgetattr(STDIN_FILENO, &(new_term));
		// new_term.c_lflag &= ~ICANON; // 이 플래그가 on되어있으면 정규모드 off면 비정규모드이다.
	// 정규모드 : 터미널 기본입력모드로 한줄씩 받는것이다. 비정규모드 : 한글자씩 받는것이다.
		new_term.c_lflag &= ~(ISIG); // off하면 반향되지않는다. 즉 입력받지 않음 abc입력해도 안뜸
		// new_term.c_cc[VMIN] = 1; // 한글자를 받을때까지
		// new_term.c_cc[VTIME] = 0; // 한무대기
		tcsetattr(STDIN_FILENO, TCSANOW, &(new_term));
		// ft_signal_heredoc();
		// ft_termios_isig(pline);
		// signal(SIGINT, SIG_IGN); // CTRL + C
		// signal(SIGQUIT, SIG_IGN);	// 평소 그리고 히어독은 그냥 무시하기 위해
		printf("1\n");
		close(fd[1]);
		waitpid(pid, NULL, 0);
		tcsetattr(STDIN_FILENO, TCSANOW, &(org_term));
		while(1);
	}
	if (pid == 0)
		ft_child_heredoc(fd);
}
