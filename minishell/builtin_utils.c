/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:09:49 by dha               #+#    #+#             */
/*   Updated: 2022/03/29 18:44:58 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
