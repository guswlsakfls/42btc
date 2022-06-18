/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:44:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/17 16:27:12 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit_obj(t_elem sp, t_ray *ray, t_hitrecord *hit_record)
{
	int	hit_result;

	hit_result = FALSE;
	hit_result = hit_sphere(sp, ray, hit_record);
	return (hit_result);
}

int	hit_something(t_hitrecord *hit_record, t_hitrecord *temp, t_vec3 color)
{
	temp->tmax = temp->t;
	*hit_record = *temp;
	hit_record->color = color;
	return (TRUE);
}

int	hit(t_info info, t_ray *ray, t_hitrecord *hit_record)
{
	int			hit_anything;
	t_hitrecord	temp;

	temp = *hit_record;
	hit_anything = FALSE;
	while (info.pl)
	{
		if (hit_plane(*info.pl, ray, &temp))
			hit_anything = hit_something(hit_record, &temp, info.pl->color);
		info.pl = info.pl->next;
	}
	while (info.sp)
	{
		if (hit_sphere(*info.sp, ray, &temp) == TRUE)
			hit_anything = hit_something(hit_record, &temp, info.sp->color);
		info.sp = info.sp->next;
	}
	while (info.cy)
	{
		if (hit_cylinder(*info.cy, *ray, &temp) != FALSE)
			hit_anything = hit_something(hit_record, &temp, info.cy->color);
		info.cy = info.cy->next;
	}
	return (hit_anything);
}

int	hit_plane(t_elem plane, t_ray *ray, t_hitrecord *hit_record)
{
	double	denom;
	double	t;

	denom = vec_dot_vec(plane.normal, vec_unit(ray->dir));
	if (!denom)
		return (0);
	t = vec_dot_vec(vec_minus_vec(plane.pos, ray->orig), plane.normal) / denom;
	if (t > EPSILON && t < hit_record->tmax)
	{
		hit_record->t = t;
		hit_record->normal = plane.normal;
		hit_record->p = ray_at(ray, t);
		hit_record->p = vec_plus_vec(hit_record->p,
				vec_mult(hit_record->normal, EPSILON));
		if (plane.diam != -1)
			if (vec_length(vec_minus_vec(plane.pos, hit_record->p))
				> (plane.diam))
				return (FALSE);
		set_face_normal(ray, hit_record);
		return (TRUE);
	}
	return (0);
}
