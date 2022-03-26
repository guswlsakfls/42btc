/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:36:41 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/26 21:22:47 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value(char *key, t_list *envs)
{
	while (envs && ft_strncmp(((t_env *)envs->content)->key, \
		key, ft_strlen(key) + 1))
	{
		envs = envs->next;
	}
	if (envs)
		return (((t_env *)envs->content)->value);
	else
		return ("");
}

int	ft_envcnt(char *str)
{
	int	cnt;
	int	flag;

	cnt = 0;
	flag = 0;
	while (*str)
	{
		while (*str != '$' && *str)
		{
			flag ^= (*str == '\'' && flag < 2);
			flag ^= (*(str++) == '\"' && (flag == 0 || flag > 1)) << 1;
		}
		if (*str == '\0')
			break ;
		if (!(ft_isalnum(*(++str)) && *str != '?') || flag & 1)
			continue ;
		cnt++;
		while (ft_isalnum(*str) || *str == '?')
			str++;
	}
	return (cnt);
}

void	get_env_values(char **values, char **cmd, t_list *envs)
{
	int		flag;
	int		*idx;
	char	*key;

	flag = 0;
	idx = ft_malloc(sizeof(int), 3);
	while ((*cmd)[idx[0]])
	{
		while ((*cmd)[idx[0]] != '$' && (*cmd)[idx[0]])
		{
			flag ^= ((*cmd)[idx[0]] == '\'' && !(flag & 2));
			flag ^= ((*cmd)[idx[0]++] == '\"' && !(flag & 1)) << 1;
		}
		if ((*cmd)[idx[0]++] == '\0')
			break ;
		if ((!ft_isalnum((*cmd)[idx[0]]) && (*cmd)[idx[0]] != '?') || flag & 1)
			continue ;
		idx[1] = idx[0];
		while (ft_isalnum((*cmd)[idx[0]]) || (*cmd)[idx[0]] == '?')
			idx[0]++;
		key = ft_substr(*cmd, idx[1], idx[0] - idx[1]);
		values[idx[2]++] = env_value(key, envs);
		free(key);
	}
	free(idx);
}

void	append_env_values_iter(char **values, char **cmd, \
	char *new_cmd, int *idx)
{
	while ((*cmd)[idx[1]] || *values)
	{
		while ((*cmd)[idx[1]] != '$' && (*cmd)[idx[1]])
		{
			idx[4] ^= ((*cmd)[idx[1]] == '\'' && !(idx[4] & 2));
			idx[4] ^= ((*cmd)[idx[1]] == '\"' && !(idx[4] & 1)) << 1;
			new_cmd[idx[0]++] = (*cmd)[idx[1]++];
		}
		if ((*cmd)[idx[1]] == '$' && idx[4] & 1)
			new_cmd[idx[0]++] = (*cmd)[idx[1]];
		if ((*cmd)[idx[1]++] == '\0')
			break ;
		if ((!ft_isalnum((*cmd)[idx[1]]) && (*cmd)[idx[1]] != '?' \
			&& (*cmd)[idx[1]] != '_') || idx[4] & 1)
			continue ;
		while (ft_isalnum((*cmd)[idx[1]]) || (*cmd)[idx[1]] == '?' || \
			(*cmd)[idx[1]] == '_')
			idx[1]++;
		idx[2] = 0;
		while ((*values)[idx[2]])
			new_cmd[idx[0]++] = (*values)[idx[2]++];
		values++;
	}
}

void	append_env_values(char **values, char **cmd)
{
	int		len;
	int		*idx;
	char	*new_cmd;

	len = ft_strlen(*cmd);
	idx = ft_malloc(sizeof(int), 5);
	while (values[idx[3]])
		len += ft_strlen(values[idx[3]++]);
	new_cmd = ft_malloc(sizeof(char), len + 1);
	append_env_values_iter(values, cmd, new_cmd, idx);
	free(*cmd);
	free(idx);
	*cmd = new_cmd;
}
