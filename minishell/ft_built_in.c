/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:32:42 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/25 19:13:18 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_built_in(char **cmds, t_list *env)
{
    t_list *list;

    list = env;
    if ((ft_strncmp(cmds[0], "echo", 5)) == 0)
        ft_echo(cmds);
    else if ((ft_strncmp(cmds[0], "cd", 3)) == 0)
        ft_cd(cmds, env);
    else if ((ft_strncmp(cmds[0], "pwd", 4)) == 0)
        // ft_pwd();
        printf("echo\n");
    else if ((ft_strncmp(cmds[0], "env", 4)) == 0)
        // ft_env();
        printf("echo\n");
    else if ((ft_strncmp(cmds[0], "export", 7)) == 0)
        // ft_export();
        printf("echo\n");
    else if ((ft_strncmp(cmds[0], "unset", 6)) == 0)
        // ft_unset();
        printf("echo\n");
    else if ((ft_strncmp(cmds[0], "exit", 5)) == 0)
        // ft_exit();
        printf("echo\n");
    else
        return (false);
    return (true);
}

int ft_check_built_in(char *cmd)
{
    if ((ft_strncmp(cmd, "echo", 5)) == 0)
        return (true);
    else if ((ft_strncmp(cmd, "cd", 3)) == 0)
        return (true);
    else if ((ft_strncmp(cmd, "pwd", 4)) == 0)
        return (true);
    else if ((ft_strncmp(cmd, "env", 4)) == 0)
        return (true);
    else if ((ft_strncmp(cmd, "export", 7)) == 0)
        return (true);
    else if ((ft_strncmp(cmd, "unset", 6)) == 0)
        return (true);
    else if ((ft_strncmp(cmd, "exit", 5)) == 0)
        return (true);
    return (false);
}

void ft_echo(char **cmds)
{
    int i;
    int option;

    option = true;
    i = 1;
    if (cmds[i] && ft_strncmp(cmds[i], "-n", 3) == false)
    {
        option = false;
        i++;
    }
    while (cmds[i])
    {
        ft_putstr_fd(cmds[i], 1);
        if (cmds[i + 1] == NULL)
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (option)
        ft_putchar_fd('\n', 1);
}

bool ft_check_pwd(char *pwd)
{
    if (chdir(pwd) == ERROR)
    {
        // error_2("cd", path, strerror(errno), 1);
        // exit_num_set(1);
        return (false);
    }
    return (true);
}

void ft_cd(char **cmds, t_list *env)
{
    char *prev_pwd;
    char *cur_pwd;

    prev_pwd = ft_get_value(env, "PWD"); // 현재 위치 가짐.
    if (prev_pwd < 0)
        exit(1);
    if (cmds[1] == NULL || ft_strncmp(cmds[1], "~", 2) == 0)
        cur_pwd = ft_get_value(env, "HOME");
    else
        cur_pwd = cmds[1];
    if (ft_check_pwd(cur_pwd) == false)
        return;
    // ft_reset_cd(env, prev_pwd);
}