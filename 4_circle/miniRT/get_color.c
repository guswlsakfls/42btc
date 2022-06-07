/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:37:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:37:05 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

bool	ft_isrgb(int n)
{
	if (n >= 0 && n <= 255)
		return (true);
	return (false);
}

int		get_color(char *str)
{
	int		color;
	int		temp;
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (check_split(split) != 3)
		exit(1);
	color = 0;
	i = 0;
	while (i < 3)
	{
		if (ft_str_isint(split[i]) == false)
			exit(1);
		temp = ft_atoi(split[i]);
		if (ft_isrgb(temp) == false)
			exit(1);
		color = (color << 8) | temp;
		i++;
	}
	free_split(split, check_split(split));
	return (color);
}
