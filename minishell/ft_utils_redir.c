/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:22:48 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/03 14:27:20 by hyujo            ###   ########.fr       */
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
			exit(0);
		}
		if (ft_strncmp(input, heredoc->str, 0) != 0)
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
		{
			if (ft_iredir(ifile, pline) == 1)
			{
				if (pline->file_fd[0] != 0)
					close(pline->heredoc_fd[0]);
			}
			return (1);
		}
		if (ifile->next == NULL)
			break ;
		ifile = ifile->next;
	}
	if (ifile && ((t_token *)ifile->content)->type == HEREDOC)
		ft_hredir(pline);
	return (0);
}
