/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:40:24 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 12:30:59 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	phong_lightning(t_rt *rt, t_hitrecord *hit_record)
{
	t_vec3	light_color;
	t_elem	*lights;

	if (!hit_record)
		exit(10);
	light_color = vec3(0, 0, 0);
	lights = rt->info.light;
	rt->ambient = vec_mult(vec_divide(rt->info.amb->color, 255),
			rt->info.amb->ratio);
	while (lights)
	{
		light_color = vec_plus_vec(light_color,
				point_light_get(rt, lights, hit_record));
		lights = lights->next;
	}
	light_color = vec_plus_vec(light_color, rt->ambient);
	return (vec_min(vec_mult_vec(light_color, rt->albedo), vec3(1, 1, 1)));
}

t_vec3	point_light_get(t_rt *rt, t_elem *light, t_hitrecord *hit_record)
{
	t_pl	pl;

	pl.light_dir = vec_minus_vec(light->pos, hit_record->p);
	pl.light_len = vec_length(pl.light_dir);
	pl.light_ray = init_ray(vec_plus_vec(hit_record->p,
				vec_mult(hit_record->normal, EPSILON)), pl.light_dir);
	if (in_shadow(rt->info, pl.light_ray, pl.light_len) == TRUE)
		return (vec3(0, 0, 0));
	pl.light_dir = vec_unit(pl.light_dir);
	pl.kd = fmax(vec_dot_vec(hit_record->normal, pl.light_dir), 0.0);
	pl.diffuse = vec_mult(light->color, pl.kd);
	pl.diffuse = vec_divide(pl.diffuse, 255);
	pl.view_dir = vec_unit(vec_mult(rt->ray.dir, -1));
	pl.reflect_dir = reflect(vec_mult(pl.light_dir, -1), hit_record->normal);
	pl.ksn = KSN;
	pl.ks = KS;
	pl.spec = pow(fmax(vec_dot_vec(pl.view_dir, pl.reflect_dir), 0.0), pl.ksn);
	pl.specular = vec_mult(vec_mult(light->color, pl.ks), pl.spec);
	pl.specular = vec_divide(pl.specular, 255);
	pl.brightness = light->ratio * LUMEN;
	return (vec_mult(vec_plus_vec(vec_plus_vec(rt->ambient, pl.diffuse),
				pl.specular), pl.brightness));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vec_minus_vec(v, vec_mult(n, vec_dot_vec(v, n) * 2)));
}

int	in_shadow(t_info info, t_ray light_ray, double light_len)
{
	t_hitrecord	hit_record;

	hit_record.tmin = 0;
	hit_record.tmax = light_len;
	if (hit(info, &light_ray, &hit_record))
		return (TRUE);
	return (FALSE);
}
