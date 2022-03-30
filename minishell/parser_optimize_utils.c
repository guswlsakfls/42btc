/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:36:41 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/30 10:53:22 by dha              ###   ########seoul.kr  */
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

int	is_env_char(int	n)
{
	if (ft_isalnum(n) || n == '?' || n == '_' || n == '{' || n == '}')
		return (1);
	return (0);
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
		if (!is_env_char(*(++str)) || flag & 1)
			continue ;
		cnt++;
		while (is_env_char(*str))
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
		if ((*cmd)[idx[0]] == '\0')
			break ;
		if (!is_env_char((*cmd)[++idx[0]]) || flag & 1)
			continue ;
		if ((*cmd)[idx[0]] == '{')
			idx[0]++;
		idx[1] = idx[0];
		while (is_env_char((*cmd)[idx[0]]) && (*cmd)[idx[0]] != '}')
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
		if ((*cmd)[idx[1]] == '\0')
			break ;
		if ((*cmd)[idx[1]] == '$' && idx[4] & 1)
			new_cmd[idx[0]++] = (*cmd)[idx[1]];
		if (!is_env_char((*cmd)[++idx[1]]) || idx[4] & 1)
			continue ;
		while (is_env_char((*cmd)[idx[1]]))
			idx[1]++;
		idx[2] = 0;
		while ((*values)[idx[2]])
			new_cmd[idx[0]++] = (*values)[idx[2]++];
		values++;
	}
}
