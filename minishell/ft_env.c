/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:14:17 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/30 12:52:14 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_exit_status(t_list	**envs)
{
	t_env	*env;

	env = (t_env *)ft_malloc(sizeof(t_env), 1);
	env->key = ft_strdup("?");
	env->value = ft_itoa(0);
	ft_lstadd_back(envs, ft_lstnew(env));
}

char	*ft_get_value(t_list *env, char *key)
{
	t_list	*list;

	list = env;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->key, key, ft_strlen(key)) == 0)
			return (((t_env *)list->content)->value);
		list = list->next;
	}
	return (NULL);
}

char	**ft_join_env(t_list *env)
{
	t_list	*list;
	char	**envp;
	int		size;
	char	*tmp;

	size = ft_lstsize(env);
	envp = malloc(sizeof(char *) * size + 1);
	list = env;
	size = 0;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->key, "?", 2) == 0)
		{
			list = list->next;
			continue ;
		}
		tmp = ft_strjoin(((t_env *)list->content)->key, "=");
		envp[size] = ft_strjoin(tmp, ((t_env *)list->content)->value);
		list = list->next;
		size++;
		free(tmp);
	}
	envp[size] = NULL;
	return (envp);
}

char	*ft_get_envp(char *cmd, t_list *env, char *key)
{
	int			i;
	char		**values;
	char		*value_list;
	char		*value;
	struct stat	file_info;

	values = ft_split(ft_get_value(env, key), ':');
	i = -1;
	while (values[++i])
	{
		value_list = ft_strjoin(values[i], "/");
		value = ft_strjoin(value_list, cmd);
		if (stat(value, &file_info) == 0)
		{
			ft_free_two(&values);
			free(value_list);
			return (value);
		}
		free(value_list);
		if (values[i + 1] == NULL)
			break ;
		free(value);
	}
	ft_free_two(&values);
	return (value);
}

t_list	*ft_init_envs(char **envp)
{
	t_list	*envs;
	t_env	*env;
	int		idx[2];

	idx[0] = 0;
	envs = NULL;
	while (envp[idx[0]])
	{
		idx[1] = 0;
		env = (t_env *)ft_malloc(sizeof(t_env), 1);
		while (envp[idx[0]][idx[1]] != '=')
			idx[1]++;
		envp[idx[0]][idx[1]] = '\0';
		env->key = ft_substr(envp[idx[0]], 0, idx[1]);
		if (ft_strncmp(env->key, "SHLVL", 6) == 0)
			env->value = ft_itoa(ft_atoi(envp[idx[0]] + idx[1] + 1) + 1);
		else
			env->value = ft_strdup(envp[idx[0]] + idx[1] + 1);
		ft_lstadd_back(&envs, ft_lstnew(env));
		idx[0]++;
	}
	ft_init_exit_status(&envs);
	return (envs);
}
