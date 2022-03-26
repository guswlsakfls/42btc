/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:57:59 by dha               #+#    #+#             */
/*   Updated: 2022/03/26 20:56:18 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	swap_value(char *value, t_list *envs)
{
	free(((t_env *)envs->content)->value);
	((t_env *)envs->content)->value = value;
	return (0);
}

int	export_arg(char *arg, t_list **envs)
{
	int		idx;
	t_env	*env;
	t_list	*tmp;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (error_invalid_identifier("export", arg));
	idx = 1;
	while (arg[idx] && arg[idx] != '=')
	{
		if (!(ft_isalnum(arg[idx]) || arg[idx] == '_'))
			return (error_invalid_identifier("export", arg));
		idx++;
	}
	tmp = *envs;
	if (is_exist_key(ft_substr(arg, 0, idx), &tmp))
		return (swap_value(ft_substr(arg, idx + 1, \
			ft_strlen(arg) - (idx + 1)), tmp));
	env = ft_malloc(sizeof(t_env), 1);
	env->key = ft_substr(arg, 0, idx);
	if (arg[idx])
		env->value = ft_substr(arg, idx + 1, ft_strlen(arg) - (idx + 1));
	ft_lstadd_back(envs, ft_lstnew(env));
	return (0);
}
