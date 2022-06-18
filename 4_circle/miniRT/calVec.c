/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calVec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:40:02 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 10:27:03 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	point3(double x, double y, double z)
{
	t_vec3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_vec3	color3(double r, double g, double b)
{
	t_vec3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

void	vec_set(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double	vec_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
