/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:33:03 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/30 16:50:19 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_heredoc(t_pline *pline, t_token *heredoc, t_list *env)
{
	char	*input;

	close(pline->heredoc_fd[0]);
	while (1)
	{
		input = ft_readline("heredoc", env);
		if (!input)
		{
			ft_putstr_fd("\x1b[1A", 1);
			ft_putstr_fd("\033[2C", 1);
			exit(0);
		}
		if (ft_strncmp(input, heredoc->str, ft_strlen(heredoc->str) != 0))
		{
			ft_putstr_fd(input, pline->heredoc_fd[1]);
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

void	ft_input_heredoc(t_list *ifile, t_pline *pline,
		t_mini *mini, t_list *env)
{
	pid_t	pid;
	t_token	*heredoc;

	if (pline->heredoc_fd[0] != 0)
		close(pline->heredoc_fd[0]);
	heredoc = (t_token *)ifile->content;
	if (pipe(pline->heredoc_fd) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		close(pline->heredoc_fd[1]);
		waitpid(pid, &(mini->statlog), WUNTRACED);
	}
	if (pid == 0)
		ft_child_heredoc(pline, heredoc, env);
}

int	ft_iredir(t_list *ifile, t_pline *pline)
{
	if (pline->file_fd[0] != 0)
		close(pline->file_fd[0]);
	pline->file_fd[0] = open(((t_token *)ifile->content)->str, O_RDONLY, 0777);
	if (pline->file_fd[0] < 0)
		return (ft_error_print(((t_token *)ifile->content)->str,
				"No such file or directory", 1));
	return (0);
}

void	ft_hredir(t_pline *pline)
{
	if (pline->file_fd[0] != 0)
		close(pline->file_fd[0]);
	pline->file_fd[0] = pline->heredoc_fd[0];
}

int	ft_redir_ifile(t_pline *pline, t_list *ifile)
{
	while (ifile)
	{
		if (((t_token *)ifile->content)->type == IREDIR)
			return (ft_iredir(ifile, pline));
		if (ifile->next == NULL)
			break ;
		ifile = ifile->next;
	}
	if (ifile && ((t_token *)ifile->content)->type == HEREDOC)
		ft_hredir(pline);
	return (0);
}

int	ft_redir_ofile(t_pline *pline, t_list *ofile)
{
	while (ofile)
	{
		if (((t_token *)ofile->content)->type == OREDIR)
		{
			if (pline->file_fd[1] != 0)
				close(pline->file_fd[1]);
			pline->file_fd[1] = open(((t_token *)ofile->content)->str,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (pline->file_fd[1] < 0)
				return (ft_error_print(((t_token *)ofile->content)->str,
						"No such file or directory", 1));
		}
		else
		{
			if (pline->file_fd[1] != 0)
			{
				close(pline->file_fd[1]);
				pline->file_fd[1] = 0;
			}
			pline->file_fd[1] = open(((t_token *)ofile->content)->str,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (pline->file_fd[1] < 0)
				return (ft_error_print(((t_token *)ofile->content)->str,
						"No such file or directory", 1));
		}
		ofile = ofile->next;
	}
	return (0);
}

void	ft_get_heredoc(t_list *plines, t_mini *mini, t_list *env)
{
	t_list	*ifile;

	while (plines)
	{
		ifile = ((t_pline *)plines->content)->ifile;
		while (ifile)
		{
			if (((t_token *)ifile->content)->type == HEREDOC)
				ft_input_heredoc(ifile, (t_pline *)plines->content, mini, env);
			if (mini->statlog == 256)
				return ;
			ifile = ifile->next;
		}
		plines = plines->next;
	}
}

int	ft_redirection(t_list *plines, t_mini *mini, t_list *env)
{
	t_list	*ifile;
	t_list	*ofile;
	t_list	*cur_plines;
	t_pline	*pline;
	int		status;

	status = 0;
	cur_plines = plines;
	ft_get_heredoc(cur_plines, mini, env);
	if (mini->statlog == 256)
		return (1);
	cur_plines = plines;
	while (cur_plines)
	{
		pline = (t_pline *)cur_plines->content;
		ifile = ((t_pline *)cur_plines->content)->ifile;
		status = ft_redir_ifile(pline, ifile);
		ofile = ((t_pline *)cur_plines->content)->ofile;
		ft_redir_ofile(pline, ofile);
		cur_plines = cur_plines->next;
	}
	return (status);
}
