/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:36:53 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:36:53 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

static int	ft_isvalidchar(char c)
{
	if ((c == 'A' || c == 'C' || c == 'L') || (c == 's' || c == 'p')
		|| (c >= '0' && c <= '9') || (c == '-') || (c == '+') || (c == '.')
		|| c == 'l' || (c == ',') || (c == ' ') || (c == '\n') || c == 'c'
		|| c == 'y')
		return (1);
	return (0);
}

int	check_split(char **s)
{
	int	re;

	re = 0;
	while (s[re] != 0)
		re++;
	return (re);
}

void	info_line_split(t_info *info, int id)
{
	static int	info_qty[6] = {3, 4, 4, 4, 4, 6};
	int			i;

	i = 0;
	while (info->line[i])
	{
		if (ft_isvalidchar(info->line[i]) == 0)
			msg_exit("Char input ");
		i++;
	}
	info->split = ft_split(info->line, ' ');
	if (check_split(info->split) != info_qty[id])
		msg_exit("elem input ");
}

int	ft_exit_hook(void)
{
	exit(0);
}
