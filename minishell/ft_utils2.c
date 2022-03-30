/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:28:12 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/30 19:42:54 by hyujo            ###   ########.fr       */
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
