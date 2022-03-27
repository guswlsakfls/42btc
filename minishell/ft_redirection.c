/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:33:03 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/27 21:24:05 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_child_heredoc(t_pline *pline, t_token *heredoc)
{
	char	*input;

	close(pline->heredoc_fd[0]);
	while (1)
	{
		input = ft_readline("heredoc");
		if (!input)
		{
			ft_putstr_fd("\x1b[1A", 1);
			ft_putstr_fd("\033[2C", 1);
			exit(0);
		}
		if (ft_strncmp(input, heredoc->str, ft_strlen(heredoc->str) != 0))
		{
			ft_putstr_fd(input, pline->heredoc_fd[1]); // 계속 데이터가 fd 파일에 쌓인다.
			ft_putstr_fd("\n", pline->heredoc_fd[1]);
			free(input);
		}
		else
		{
			free(input);
			exit(0);
		}
	}
}

// void	ft_termios_isig(t_pline *pline)
// {
// 	tcgetattr(STDIN_FILENO, &(pline->org_term));
// 	// pline->org_term.c_lflag &= ~ICANON; // 이 플래그가 on되어있으면 정규모드 off면 비정규모드이다.
// 	// 정규모드 : 터미널 기본입력모드로 한줄씩 받는것이다. 비정규모드 : 한글자씩 받는것이다.
// 	// pline->org_term.c_lflag &= ~ECHO; // off하면 반향되지않는다. 즉 입력받지 않음 abc입력해도 안뜸
// 	pline->org_term.c_lflag &= ~ISIG;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &(pline->org_term));
// }

// void	ft_termios_isig(t_pline *pline)
// {
// 	tcgetattr(STDIN_FILENO, &(pline->org_term));
// 	tcgetattr(STDIN_FILENO, &(pline->new_term));
// 	pline->org_term.c_lflag &= ~ICANON; // 이 플래그가 on되어있으면 정규모드 off면 비정규모드이다.
// 	// 정규모드 : 터미널 기본입력모드로 한줄씩 받는것이다. 비정규모드 : 한글자씩 받는것이다.
// 	pline->org_term.c_lflag &= ~ECHO; // off하면 반향되지않는다. 즉 입력받지 않음 abc입력해도 안뜸
// 	// pline->new_term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &(pline->new_term));
// }

void	ft_input_heredoc(t_list *ifile, t_pline *pline)
{
	pid_t	pid;
	t_token	*heredoc;
	struct termios	org_term;
	struct termios	new_term;

	if (pline->heredoc_fd[0] != 0) // heredoc 도 0 으로 초기화 해서 들어와야함.
		close(pline->heredoc_fd[0]);
	heredoc = (t_token *)ifile->content;
	if (pipe(pline->heredoc_fd) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
	{
		tcgetattr(STDIN_FILENO, &(org_term));
		tcgetattr(STDIN_FILENO, &(new_term));
		pline->org_term.c_lflag &= ~ISIG;
		tcsetattr(STDIN_FILENO, TCSANOW, &(new_term));
		ft_signal_heredoc();
		// ft_termios_isig(pline);
		// signal(SIGINT, SIG_IGN); // CTRL + C
		// signal(SIGQUIT, SIG_IGN);	// 평소 그리고 히어독은 그냥 무시하기 위해
		close(pline->heredoc_fd[1]);
		waitpid(pid, NULL, WUNTRACED);
		// tcsetattr(STDIN_FILENO, TCSANOW, &(pline->org_term));
	}
	if (pid == 0)
		ft_child_heredoc(pline, heredoc);
}

int	ft_iredir(t_list *ifile, t_pline *pline)
{
	if (pline->file_fd[0] != 0) // 중복해서 열려 있으면 닫아주고 다시 연다.
	{
		close(pline->file_fd[0]);
		pline->file_fd[0] = 0;
	}
	pline->file_fd[0] = open(((t_token *)ifile->content)->str, O_RDONLY, 0777);
	if (pline->file_fd[0] < 0)
	{
		printf("bash: %s: No such file or directory\n", ((t_token *)ifile->content)->str);
		// exit(1);
	}
	if (!(ifile->next))
	{
		if (pline->heredoc_fd[0])
			close(pline->heredoc_fd[0]);
		return (1);
	}
	return (0);
}

void	ft_hredir(t_pline *pline)
{
	if (pline->file_fd[0] != 0) // 중복해서 열려 있으면 닫아주고 다시 연다.
		close(pline->file_fd[0]);
	// 복제해서 사용해야 하는데
	pline->file_fd[0] = pline->heredoc_fd[0];
}

void	ft_redir_ifile(t_pline *pline, t_list *ifile)
{
	while (ifile)
	{
		// < 일 때
		if (((t_token *)ifile->content)->type == IREDIR)
		{
			if (ft_iredir(ifile, pline) == 1)
				break ;
		}
		// << 일 때, here_doc 이다.
		else
			ft_hredir(pline);
		ifile = ifile->next;
	}
}

void ft_redir_ofile(t_pline *pline, t_list *ofile)
{
	while (ofile)
	{
		// > 일 때
		if (((t_token *)ofile->content)->type == OREDIR)
		{
			if (pline->file_fd[1] != 0)
				close(pline->file_fd[1]);
			pline->file_fd[1] = open(((t_token *)ofile->content)->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (pline->file_fd[1] < 0)
				exit(1);
		}
		else
		{
			if (pline->file_fd[1] != 0)
			{
				close(pline->file_fd[1]);
				pline->file_fd[1] = 0;
			}
			pline->file_fd[1] = open(((t_token *)ofile->content)->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (pline->file_fd[1] < 0)
				exit(1);
		}
		ofile = ofile->next;
	}
}

void	ft_get_heredoc(t_list *list)
{
	t_list *ifile;

	while (list)
	{
		ifile = ((t_pline *)list->content)->ifile;
		while (ifile)
		{
			if (((t_token *)ifile->content)->type == HEREDOC)
				ft_input_heredoc(ifile, (t_pline *)list->content);
			ifile = ifile->next;
		}
		list = list->next;
	}
}

void ft_redirection(t_list *plines) // file open 이 에러가 나면 에러 메시지 띄우고 다음 파일 오픈으로 감
{
	t_list	*ifile;
	t_list	*ofile;
	t_list	*list;
	t_pline	*pline;

	list = plines;
	// heredoc 나오면 제일 먼저 임시파일 만들어 준다. heredoc 찾기 위해 한바퀴
	ft_get_heredoc(list);
	list = plines;
	while (list)
	{
		pline = (t_pline *)list->content;
		ifile = ((t_pline *)list->content)->ifile;
		ft_redir_ifile(pline, ifile);
		ofile = ((t_pline *)list->content)->ofile;
		ft_redir_ofile(pline, ofile);
		list = list->next;
	}
}
