/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:28:12 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/03 14:01:38 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_fork(t_pline *cur, t_pline *prev)
{
	if ((prev && prev->is_pipe == ISPIPE) || cur->is_pipe == ISPIPE
		|| ft_check_built_in(cur->cmds[0]) == 1)
		cur->pid = fork();
	if (cur->pid < 0)
		exit(0);
}

void	ft_init_exit_status(t_list	**envs)
{
	t_env	*env;

	env = (t_env *)ft_malloc(sizeof(t_env), 1);
	env->key = ft_strdup("?");
	env->value = ft_itoa(0);
	ft_lstadd_back(envs, ft_lstnew(env));
}
