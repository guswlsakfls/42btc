/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:36:03 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/29 20:57:24 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_removal(char **cmd)
{
	int		flag;
	int		idx;
	char	*tmp;

	flag = 0;
	idx = 0;
	while ((*cmd)[idx])
	{
		while (((*cmd)[idx] == '\'' && !(flag & 2)) || \
			((*cmd)[idx] == '\"' && !(flag & 1)))
		{
			flag ^= ((*cmd)[idx] == '\'' && !(flag & 2));
			flag ^= ((*cmd)[idx] == '\"' && !(flag & 1)) << 1;
			ft_strlcpy(*cmd + idx, *cmd + idx + 1, ft_strlen(*cmd + idx));
		}
		idx++;
	}
	tmp = *cmd;
	*cmd = ft_strdup(*cmd);
	free(tmp);
}

void	env_expansion(char **cmd, t_list *envs)
{
	int		env_cnt;
	char	**values;

	env_cnt = ft_envcnt(*cmd);
	if (ft_strchr(*cmd, '$') == NULL || !env_cnt)
		return ;
	values = ft_malloc(sizeof(char *), env_cnt + 1);
	get_env_values(values, cmd, envs);
	append_env_values(values, cmd);
	free(values);
}

void	expansion(char **cmd, t_list *envs)
{
	env_expansion(cmd, envs);
	quote_removal(cmd);
}

void	optimize(t_list *plines, t_list *envs)
{
	int		idx;
	t_list	*tmp_ifile;
	t_list	*tmp_ofile;

	if (plines == NULL)
		return ;
	while (plines)
	{
		idx = 0;
		tmp_ifile = ((t_pline *)plines->content)->ifile;
		tmp_ofile = ((t_pline *)plines->content)->ofile;
		while (((t_pline *)plines->content)->cmds[idx])
			expansion(&((t_pline *)plines->content)->cmds[idx++], envs);
		while (tmp_ifile)
		{
			expansion(&((t_token *)tmp_ifile->content)->str, envs);
			tmp_ifile = tmp_ifile->next;
		}
		while (tmp_ofile)
		{
			expansion(&((t_token *)tmp_ofile->content)->str, envs);
			tmp_ofile = tmp_ofile->next;
		}
		plines = plines->next;
	}
}
