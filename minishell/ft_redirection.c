/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:33:03 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/18 19:16:09 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_here_doc(t_pline pline, t_list infile)
{
	char	*input;
	pit_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pipe(pline->pipe_fd) < 0)
		exit(1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(1);
		if (ft_strncmp(input, infile->name, ft_strlen(infile->name)) != 0)
		{
			ft_putstr_fd(input, pline->pipe_fd[1]); // 계속 데이터가 fd 파일에 쌓인다.
			ft_putstr_fd("\n", pline->pipe_fd[1]);
		}
		else
		{
			close(pipe_fd[1]);
			free(input);
			break ;
		}
		free(input);
	}
	close(fd);
}

void	ft_redir(t_pline pline) // file open 이 에러가 나면 에러 메시지 띄우고 다음 파일 오픈으로 감
{
	t_list	infile;
	t_list	heredoc;
	t_list	outfile;
	int		fd;

	infile = pline->infile;
	outfile = pline->outfile;
	// heredoc 나오면 제일 먼저 임시파일 만들어 준다.
	heredoc = pline->infile;
	while (heredoc)
	{
		if (heredoc->type == HEREDOC)
			ft_here_doc(infile, fd);
		heredoc->next;
	}
	while (infile)
	{
		// < 일 때
		if (infile->type == IREDIR)
		{
			fd = open(infile->name, O_RDONLY, 0777);
			if (fd < 0)
				exit(1);
		}
		// << 일 때, here_doc 이다.
		else
		{
			fd = open(".tmp_heredoc", O_RDONLY, 0777);
			if (fd < 0)
				exit(1);
		}
		if (infile->type == IREDIR)
		{
			fd = open(infile->name, O_RDONLY, 0777);
			if (fd < 0)
				exit(1);
		}
		if (!(infile->next))
		{
			// dup2(fd, STDIN_FILENO); // 모든 입력이 fd 이다. // 자식에서 dup2 로 하면 될 듯?
			// if (dup < 0)
			// 	exit(1);
			// close(fd); // file 내용은 STDIN으로 복제 했으니까 닫아도 된다. // 닫으면 fd 파일은 계속 표준입출력에 복제 되나? => 지금까지 이해는 그렇다.
			// if (inifle->type == HEREDOC)
			// 	unlink(".tmp_heredoc");
			break ;
		}
		infile = infile->next;
	}
	while (outfile)
	{
		// > 일 때
		if (outfile->type == OREDIR)
		{
			fd = open(outfile->name, O_WRONLY, O_CREAT, O_TRUNC, 0777);
			if (fd < 0)
				exit(1);
		}
		else
		{
			fd = open(outfile->name, O_WRONLY, O_CREAT, O_APPEND, 0777);
			if (fd < 0)
				exit(1);
		}
		if (!(outfile->next))
		{
			// dup2(fd, STDOUT_FILENO); // 자식에서 dup2 로 가져오면 될듯.
			// if (dup < 0)
			// 	exit(1);
			// close(fd); // file 에 stdout cmd 명령에서 넣을껀데 닫아도 상관 없나?
			break ;
		}
		outfile = outfile->next;
	}
}
