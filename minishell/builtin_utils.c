/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:09:49 by dha               #+#    #+#             */
/*   Updated: 2022/03/26 20:49:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_invalid_identifier(char *func, char *arg)
{
	ft_putstr_fd(ERR_PRPT, 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(ERR_NVI, 2);
	return (1);
}

int	is_exist_key(char *key, t_list **envs)
{
	while (*envs)
	{
		if (ft_strncmp(((t_env *)(*envs)->content)->key, key, 0) == 0)
		{
			free(key);
			return (1);
		}
		if ((*envs)->next == NULL)
			break ;
		(*envs) = (*envs)->next;
	}
	free(key);
	return (0);
}
