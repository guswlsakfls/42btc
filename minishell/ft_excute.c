/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:13:15 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/25 19:13:49 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute(char **cmds, t_list *env, char **envp)
{
    char *path;

    path = (ft_get_envp(cmds[0], env, "PATH"));
    if (execve(path, cmds, envp) < 0)
    {
        //error 처리 해주기
        exit(1);
    }
}