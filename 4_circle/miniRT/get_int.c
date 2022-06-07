/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:37:28 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:37:28 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

bool			ft_str_isint(char *str)
{
	int		i;

	i = 0;
	if (i == 0 && str[i] == '-')
			i++;
	while (i < (int)ft_strlen(str))
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int				get_int(char *str)
{
	if (ft_str_isint(str) == false)
		exit(1);
	return (ft_atoi(str));
}

int				get_posint(char *str)
{
	int		posint;

	posint = get_int(str);
	if (!(posint > 0))
		exit(1);
	return (posint);
}
