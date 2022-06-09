/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:57:02 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/09 19:47:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit_cylinder_side(t_elem *cy, t_ray *ray, t_hitRecord *hit_record)
{
	double	a;
	double	half_b;
	double	c;
	t_vec3	u;
	t_vec3	o;
	t_vec3	delta_p;
	double	r;

	double	discri;
	double	sqrtd;
	double	root;
	double	hit_height;

	u = ray->dir;
	o = cy->normal;
	r = cy->diam / 2;
	delta_p = vecMinusVec(ray->orig, cy->pos);
	// 여기 식이 조금 다른데,,,,,,
	a = vecSquared(vecCrossVec(u, o));
	half_b = vecDotVec(vecCrossVec(u, o), vecCrossVec(delta_p, o));
	c = vecSquared(vecCrossVec(delta_p, o)) - pow(r, 2);
	discri = half_b * half_b - a * c;
	if (discri < 0)
		return (FALSE);
	sqrtd = sqrt(discri);
	root = (-half_b - sqrtd) / a;
	if (root < hit_record->tmin || hit_record->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < hit_record->tmin || hit_record->tmax < root)
			return (-1);
	}
	hit_height = cy_boundary(cy, rayAt(ray, root));
	if (!hit_height)
		return (FALSE);
	hit_record->t = root;
	hit_record->p = rayAt(ray, root); // 교점의 좌표
	hit_record->normal = get_cylinder_normal(cy, hit_record->p, hit_height);
	setFaceNormal(ray, hit_record);
	return (TRUE);
}

int	hit_cylinder_cap(t_elem *cy, t_ray *ray, t_hitRecord *hit_record, double height)
{
	double	r;
	t_vec3	circle_center;
	double	root;
	double	diam;

	r = cy->diam / 2;
	circle_center = vecPlusVec(cy->pos, vecMult(cy->normal, height));
	root = vecDotVec(vecMinusVec(circle_center, ray->orig), cy->normal);
	diam = vecLength(vecMinusVec(circle_center, rayAt(ray, root)));
	if (fabs(r) < fabs(diam))
		return (FALSE);
	if (root < hit_record->tmin || hit_record->tmax < root)
		return (FALSE);
	hit_record->t = root;
	hit_record->p = rayAt(ray, root);
	hit_record->tmax = hit_record->t;
	if (0 < height)
		hit_record->normal = cy->normal;
	else
		hit_record->normal = vecMult(cy->normal, -1);
	setFaceNormal(ray, hit_record);
	return (TRUE);
}

int	hit_cylinder(t_elem *cy, t_ray *ray, t_hitRecord *hit_record)
{
	int	res;

	res = 0;
	res += hit_cylinder_cap(cy, ray, hit_record, cy->height / 2);
	res += hit_cylinder_cap(cy, ray, hit_record, -(cy->height / 2));
	// res += hit_cylinder_side(cy, ray, hit_record);
	return (res);
}

t_vec3	get_cylinder_normal(t_elem *cy, t_vec3 at_point, double hit_height)
{
	t_vec3	hit_center;
	t_vec3	normal;

	hit_center = vecPlusVec(cy->pos, vecMult(cy->normal, hit_height));
	normal = vecMinusVec(at_point, hit_center);
	return (vecUnit(normal));
}

double	cy_boundary(t_elem *cy, t_vec3 at_point)
{
	double	hit_height;
	double	max_height;

	hit_height = vecDotVec(vecMinusVec(at_point, cy->pos), cy->normal);
	max_height = cy->height / 2;
	if (fabs(hit_height) > max_height)
		return (FALSE);
	return (hit_height);
}
