/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scha <scha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:57:02 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 21:09:11 by scha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	cal_cylinder_abc(t_ray ray, t_elem cylinder)
{
	t_vec3	result;
	t_vec3	ce;

	ce = vec_minus_vec(ray.orig, cylinder.pos);
	result.x = pow(vec_dot_vec(ray.dir, cylinder.normal), 2) - 1;
	result.y = vec_dot_vec(ray.dir, cylinder.normal)
		* vec_dot_vec(ce, cylinder.normal) - vec_dot_vec(ce, ray.dir);
	result.z = pow(cylinder.diam, 2) - vec_dot_vec(ce, ce)
		+ pow(vec_dot_vec(ce, cylinder.normal), 2);
	return (result);
}

int	get_t(t_hitrecord *ret, double det, t_vec3 abc)
{
	ret->t = (-abc.y + sqrt(det)) / abc.x;
	if (ret->t < ret->tmin || ret->tmax < ret->t)
	{
		ret->t = (-abc.y - sqrt(det)) / abc.x;
		if (ret->t < ret->tmin || ret->tmax < ret->t)
			return (FALSE);
	}
	return (TRUE);
}

int	hit_cylinder(t_elem cylinder, t_ray ray, t_hitrecord *ret)
{
	t_vec3		abc;
	t_vec3		cp;
	double		det;
	int			is_hit;

	is_hit = 0;
	abc = cal_cylinder_abc(ray, cylinder);
	det = pow(abc.y, 2) - abc.x * abc.z;
	is_hit = (det >= 0);
	if (is_hit == TRUE)
	{
		if (get_t(ret, det, abc) == FALSE)
			return (FALSE);
		ret->p = vec_plus_vec(vec_mult(ray.dir, ret->t), ray.orig);
		cp = vec_minus_vec(ret->p, cylinder.pos);
		ret->normal = vec_unit(vec_minus_vec(cp, vec_mult(cylinder.normal,
						vec_dot_vec(cp, cylinder.normal))));
		if (vec_dot_vec(cp, cylinder.normal) < 0
			|| vec_dot_vec(cp, cylinder.normal) > cylinder.height)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

void	cap_in_cylinder(t_elem *cy, t_info *info)
{
	t_elem	*down_cap;
	t_elem	*up_cap;

	down_cap = (t_elem *)malloc(sizeof(t_elem));
	up_cap = (t_elem *)malloc(sizeof(t_elem));
	down_cap->pos = cy->pos;
	down_cap->normal = cy->normal;
	down_cap->diam = cy->diam;
	down_cap->next = NULL;
	down_cap->color = cy->color;
	list_add_back_elem(up_cap, &info->pl);
	up_cap->normal = cy->normal;
	up_cap->diam = cy->diam;
	up_cap->color = cy->color;
	up_cap->next = NULL;
	up_cap->pos = vec_plus_vec(cy->pos, vec_mult(cy->normal, cy->height));
	list_add_back_elem(down_cap, &info->pl);
}
