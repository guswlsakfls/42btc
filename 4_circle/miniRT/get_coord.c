/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:37:10 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:37:10 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

bool	ft_isnormal(t_vec3 normal)
{
	if (normal.x >= -1.0 && normal.x <= 1.0
		&&normal.y >= -1.0 && normal.y <= 1.0
		&&normal.z >= -1.0 && normal.z <= 1.0)
		return (true);
	return (false);
}

bool	ft_iscolor(t_vec3 color)
{
	if (color.x >= 0 && color.x <= 255.0
		&& color.y >= 0 && color.y <= 255.0
		&& color.z >= 0.0 && color.z <= 255.0)
		return (true);
	return (false);
}

t_vec3	get_vector(char *str)
{
	t_vec3	vec;
	char	**split;

	split = ft_split(str, ',');
	if (check_split(split) != 3 || !(ft_str_isdouble(split[0]) == 1
			&& ft_str_isdouble(split[1]) == 1
			&& ft_str_isdouble(split[2]) == 1))
	{
		free_split(split, check_split(split));
		msg_exit("elem input ");
	}
	vec.x = ft_atof(split[0]);
	vec.y = ft_atof(split[1]);
	vec.z = ft_atof(split[2]);
	free_split(split, check_split(split));
	return (vec);
}

t_vec3	get_normal(char *str)
{
	t_vec3	vec;

	vec = get_vector(str);
	if (ft_isnormal(vec) == false)
		msg_exit("nomarize ");
	return (vec);
}

t_vec3	get_color(char *str)
{
	t_vec3	vec;

	vec = get_vector(str);
	if (ft_iscolor(vec) == false)
		msg_exit("rgb range ");
	return (vec);
}
