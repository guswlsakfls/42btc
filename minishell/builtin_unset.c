/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:58:03 by dha               #+#    #+#             */
/*   Updated: 2022/03/26 20:49:37 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void *env)
{
	free(((t_env *)env)->key);
	free(((t_env *)env)->value);
	free(env);
}

int	unset_arg(char *arg, t_list **envs)
{
	int		idx;
	t_list	*tmp;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (error_invalid_identifier("unset", arg));
	idx = 1;
	while (arg[idx])
	{
		if (!(ft_isalnum(arg[idx]) || arg[idx] == '_'))
			return (error_invalid_identifier("unset", arg));
		idx++;
	}
	tmp = *envs;
	if (ft_strncmp(((t_env *)(*envs)->content)->key, arg, 0) == 0)
	{
		ft_lstdel_front(envs);
		return (0);
	}
	if (is_exist_key(ft_strdup(arg), &tmp))
		ft_lstdelone(tmp, free_env);
	return (0);
}

int	builtin_unset(char **argv, t_list **envs)
{
	int	idx;
	int	exit_status;

	idx = 0;
	exit_status = 0;
	if (argv[1] == NULL)
		return (0);
	while (argv[++idx])
		exit_status = unset_arg(argv[idx], envs);
	return (exit_status);
}
