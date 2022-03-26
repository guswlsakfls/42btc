/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:22:23 by dha               #+#    #+#             */
/*   Updated: 2022/03/26 20:49:47 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **argv, t_list **envs)
{
	int	idx;
	int	exit_status;

	idx = 0;
	exit_status = 0;
	if (argv[1] == NULL)
		return (export_no_arg(*envs));
	while (argv[++idx])
		exit_status = export_arg(argv[idx], envs);
	return (exit_status);
}
