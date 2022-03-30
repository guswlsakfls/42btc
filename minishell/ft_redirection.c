/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:33:03 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/30 20:34:33 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_file_fd(t_pline *pline)
{
	if (pline->file_fd[1] != 0)
	{
		close(pline->file_fd[1]);
	}
}

int	ft_redir_ofile(t_pline *pline, t_list *ofile)
{
	while (ofile)
	{
		if (((t_token *)ofile->content)->type == OREDIR)
		{
			ft_close_file_fd(pline);
			pline->file_fd[1] = open(((t_token *)ofile->content)->str,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (pline->file_fd[1] < 0)
				return (ft_error_print(((t_token *)ofile->content)->str,
						"No such file or directory", 1));
		}
		else
		{
			ft_close_file_fd(pline);
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
