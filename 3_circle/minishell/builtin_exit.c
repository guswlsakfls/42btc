/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:21:39 by dha               #+#    #+#             */
/*   Updated: 2022/03/30 22:00:15 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv, t_list **envs)
{
	unsigned char	exit_status;
	t_list			*tmp;

	exit_status = 0;
	if (isatty(0) && isatty(1))
		printf("exit\n");
	if (argv[1])
	{
		if (argv[2])
		{
			ft_putendl_fd("nano: exit: too many arguments", 2);
			return (1);
		}
		if (!ft_isnum(argv[1]))
			exit_status = error_numeric_arg("exit", ERR_NMA);
		else
			exit_status = ft_atoi(argv[1]);
	}
	tmp = *envs;
	is_exist_key(ft_strdup("?"), &tmp);
	swap_value(ft_itoa(exit_status), tmp);
	exit(exit_status);
}
