/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:08:51 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 13:24:59 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ray_color(t_ray *r, t_info info, t_rt *rt)
{
	t_vec3		rgb;
	t_hitrecord	hit_record;

	hit_record.tmin = EPSILON;
	hit_record.tmax = INFINITY;
	if (hit(info, r, &hit_record) == TRUE)
	{
		rt->albedo = vec_divide(hit_record.color, 255);
		rgb = phong_lightning(rt, &hit_record);
		return (rgb);
	}
	else
	{
		hit_record.t = 0.5 * (r->dir.y + 1.0);
		rgb = vec_plus_vec(vec_mult(color3(1.0, 1.0, 1.0),
					(1.0 - hit_record.t)), vec_mult(color3(0.5, 0.7, 1.0),
					hit_record.t));
		return (rgb);
	}
}

void	set_hit_record(t_hitrecord *hit_record, t_ray *ray,
			t_elem sp, double root)
{
	hit_record->t = root;
	hit_record->p = ray_at(ray, root);
	hit_record->normal = vec_divide(vec_minus_vec
			(hit_record->p, sp.pos), (double)sp.diam / 2);
}

int	hit_sphere(t_elem sp, t_ray *ray, t_hitrecord *hit_record)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	discri;
	double	root;

	oc = vec_minus_vec(ray->orig, sp.pos);
	a = vec_dot_vec(ray->dir, ray->dir);
	b = 2.0 * vec_dot_vec(oc, ray->dir);
	discri = b * b - 4 * a * (vec_dot_vec(oc, oc)
			- pow((double)(sp.diam / 2), 2));
	if (discri < 0)
		return (FALSE);
	root = (-b - sqrt(discri)) / (2.0 * a);
	if (root < hit_record->tmin || hit_record->tmax < root)
	{
		root = (-b + sqrt(discri)) / (2.0 * a);
		if (root < hit_record->tmin || hit_record->tmax < root)
			return (FALSE);
	}
	set_hit_record(hit_record, ray, sp, root);
	set_face_normal(ray, hit_record);
	return (TRUE);
}

void	set_face_normal(t_ray *ray, t_hitrecord *hit_record)
{
	if (vec_dot_vec(ray->dir, hit_record->normal) > 0.0)
	{
		hit_record->normal = vec_mult(hit_record->normal, -1);
		hit_record->front = FALSE;
	}
	else
		hit_record->front = TRUE;
}
