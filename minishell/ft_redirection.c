/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:33:03 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/21 22:13:51 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input_heredoc(t_list *ifile, t_pline *pline)
{
	char	*input;
	t_token	*heredoc;

	if (pline->heredoc_fd[0] != 0)
		close(pline->heredoc_fd[0]);
	heredoc = (t_token *)ifile->content;
	if (pipe(pline->heredoc_fd) < 0)
		exit(1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(1);
		if (ft_strncmp(input, heredoc->str, ft_strlen(heredoc->str) != 0))
		{
			ft_putstr_fd(input, pline->heredoc_fd[1]); // 계속 데이터가 fd 파일에 쌓인다.
			ft_putstr_fd("\n", pline->heredoc_fd[1]);
			free(input);
		}
		else
		{
			close(pline->heredoc_fd[1]);
			free(input);
			break ;
		}
	}
}

void	ft_redirection(t_list *plines) // file open 이 에러가 나면 에러 메시지 띄우고 다음 파일 오픈으로 감
{
	t_list	*ifile;
	t_list	*ofile;
	t_list	*list;
	t_pline	*pline;

	list = plines;
	// heredoc 나오면 제일 먼저 임시파일 만들어 준다. heredoc 찾기 위해 한바퀴
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
	list = plines;
	while (list)
	{
		pline = (t_pline *)list->content;
		ifile = ((t_pline *)list->content)->ifile;
		while (ifile)
		{
			// < 일 때
			if (((t_token *)ifile->content)->type == IREDIR)
			{
				if (pline->file_fd[0] != 0) // 중복해서 열려 있으면 닫아주고 다시 연다.
					close(pline->file_fd[0]);
				pline->file_fd[0] = open(((t_token *)ifile->content)->str, O_RDONLY, 0777);
				if (pline->file_fd[0] < 0)
					exit(1);
			}
			// << 일 때, here_doc 이다.
			else
			{
				pline->file_fd[0] = pline->heredoc_fd[0];
			}
			if (ifile->next == NULL)
			{ // 모든 입력이 fd 이다. // 자식에서 dup2 로 하면 될 듯?
				if (dup2(pline->file_fd[0], STDIN_FILENO) < 0)
					exit(1);
				close(pline->file_fd[0]); // file 내용은 STDIN으로 복제 했으니까 닫아도 된다. // 닫으면 fd 파일은 계속 표준입출력에 복제 되나? => 지금까지 이해는 그렇다.
				close(pline->heredoc_fd[0]);
				break ;
			}
			ifile = ifile->next;
		}
		ofile = ((t_pline *)list->content)->ofile;
		while (ofile)
		{
			// > 일 때
			if (((t_token *)ofile->content)->type == OREDIR)
			{
				if (pline->file_fd[1] != 0)
					close(pline->file_fd[1]);
				pline->file_fd[1] = open(((t_token *)ofile->content)->str, O_WRONLY, O_CREAT, O_TRUNC, 0777);
				if (pline->file_fd[1] < 0)
					exit(1);
			}
			else
			{
				if (pline->file_fd[1] != 0)
					close(pline->file_fd[1]);
				pline->file_fd[1] = open(((t_token *)ofile->content)->str, O_WRONLY, O_CREAT, O_APPEND, 0777);
				if (pline->file_fd[1] < 0)
					exit(1);
			}
			if (ofile->next == NULL)
			{
				if (dup2(pline->file_fd[1], STDOUT_FILENO) < 0) // 자식에서 dup2 로 가져오면 될듯.
					exit(1);
				close(pline->file_fd[1]); // file 에 stdout cmd 명령에서 넣을껀데 닫아도 상관 없나?
				break;
			}
			ofile = ofile->next;
		}
		list = list->next;
	}
}
