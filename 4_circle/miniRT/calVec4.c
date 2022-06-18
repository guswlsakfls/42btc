/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calVec4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:27:30 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 10:27:34 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec_unit(t_vec3 vec)
{
	double	len;

	len = vec_length(vec);
	if (len == 0)
	{
		printf("Error\n:Devider is 0");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vec3	vec_min(t_vec3 vec, t_vec3 vec2)
{
	if (vec.x > vec2.x)
		vec.x = vec2.x;
	if (vec.y > vec2.y)
		vec.y = vec2.y;
	if (vec.z > vec2.z)
		vec.z = vec2.z;
	return (vec);
}

t_vec3	vec_max(t_vec3 vec, t_vec3 vec2)
{
	if (vec.x < vec2.x)
		vec.x = vec2.x;
	if (vec.y < vec2.y)
		vec.y = vec2.y;
	if (vec.z < vec2.z)
		vec.z = vec2.z;
	return (vec);
}
