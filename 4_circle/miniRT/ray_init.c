/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:46:54 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 09:47:03 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	init_ray(t_vec3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = vec_unit(dir);
	return (ray);
}

t_vec3	ray_at(t_ray *ray, double t)
{
	t_vec3	at;

	at = vec_plus_vec(ray->orig, vec_mult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam.orig_point;
	ray.dir = vec_unit(vec_minus_vec(vec_plus_vec(vec_plus_vec(cam.left_bottom,
						vec_mult(cam.horizontal, u)),
					vec_mult(cam.vertical, v)), cam.orig_point));
	return (ray);
}
