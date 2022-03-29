/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:41:50 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/30 01:53:11 by hyunjinjo        ###   ########.fr       */
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

int	error_env_not_set(char *func, char *arg)
{
	ft_putstr_fd(ERR_PRPT, 2);
	ft_putstr_fd(func, 2);
	ft_putendl_fd(arg, 2);
	return (1);
}

int	error_numeric_arg(char *func, char *arg)
{
	ft_putstr_fd(ERR_PRPT, 2);
	ft_putstr_fd(func, 2);
	ft_putendl_fd(arg, 2);
	return (255);
}

int	ft_error_print(char *cmd, char *msg, int exitnum)
{
	ft_putstr_fd(ERR_PRPT, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (exitnum);
}
