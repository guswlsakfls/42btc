/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:14:23 by dha               #+#    #+#             */
/*   Updated: 2022/04/01 18:31:18 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argv, t_list **envs)
{
	if (argv[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": with no options or arguments", 2);
		return (1);
	}
	while (*envs)
	{
		if (ft_strncmp(((t_env *)(*envs)->content)->key, "?", 2) == 0 \
			|| ((t_env *)(*envs)->content)->value == NULL)
		{
			*envs = (*envs)->next;
			continue ;
		}
		ft_putstr_fd(((t_env *)(*envs)->content)->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(((t_env *)(*envs)->content)->value, 1);
		*envs = (*envs)->next;
	}
	return (0);
}
