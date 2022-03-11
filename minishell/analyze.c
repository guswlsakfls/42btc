/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:54:28 by dha               #+#    #+#             */
/*   Updated: 2022/03/11 11:59:19 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*analyze(char *cmd)
{
	t_list	*lst;

	lst = tokenize(cmd);
	free(cmd);
	if (lst == NULL)
		return (NULL);
	return (lst);
}
