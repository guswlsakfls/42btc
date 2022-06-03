/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:08:51 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/03 15:08:03 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	initRay(t_vec3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = vecUnit(dir);
	return (ray);
}

t_vec3	rayAt(t_ray *ray, double t)
{
	t_vec3	at;
	at = vecPlusVec(ray->orig, vecMult(ray->dir, t));
	return (at);
}

t_ray	rayPrimary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->origPoint;
	ray.dir = vecUnit(vecMinusVec(vecPlusVec(vecPlusVec(cam->leftBottom, vecMult(cam->horizontal, u)), vecMult(cam->vertical, v)), cam->origPoint));
	return (ray);
}

t_light	makeLight(t_vec3 vec, t_vec3 vec2, double t)
{
	t_light	light;

	light.orig = vec;
	light.lightColor = vec2;
	light.brightRatio = t;
	return (light);
}

// 광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴
t_vec3	rayColor(t_ray *r, t_sphere *sphere)
{
	double		t;
	t_vec3		rgb;
	t_vec3		tmp;
	// t_vec3		n;
	t_light		light;
	t_hitRecord	hit_r;

	hit_r.ambient = vecMult(vec3(1, 1, 1), 0.1); //ambient set
	t = hitSphere(sphere, r);
	if (t > 0.0)
	{
		light = makeLight(vec3(0, 5, 0), vec3(1, 1, 1), 0.5);
		tmp = phongLighting(light, hit_r);
		rgb = vecMult(tmp, 255.999);
		// 구  그라데이션
		// tmp = rayAt(r, t);
		// n = vecUnit(vec(tmp.x - 0, tmp.y - 0, tmp.z - (-1)));
		// rgb = vecMult(vec(n.x + 1, n.y + 1, n.z + 1), 0.5);
		return (rgb);
	}
	else
	{
		// 단위 벡터가 -1 1 인데 음수가 들어오면 컬러에는 음수가 없기 때문에 아래와 같이 연산한다.
		t = 0.5 * (r->dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		rgb = vecPlusVec(vecMult(color3(1.0, 1.0, 1.0), (1.0 - t)), vecMult(color3(0.5, 0.7, 1.0), t));
		return (rgb);
	}
}

double	hitSphere(t_sphere *sp, t_ray *ray)
{
	t_vec3	sp_center;
	double	a;
	double	b;
	double	c;
	double	discri; // 판별식

	sp_center = vecMinusVec(ray->orig, sp->center);
	a = vecDotVec(ray->dir, ray->dir);
	b = 2.0 * vecDotVec(sp_center, ray->dir);
	c = vecDotVec(sp_center, sp_center) - sp->radius2;
	discri = b * b - 4 * a * c;
	if (discri >= 0)
		return ((-b - sqrt(discri)) / (2.0 *a)); // hit 했음.
	return (0);
}

t_vec3	phongLighting(t_light light, t_hitRecord hit_r)
{
	t_vec3	light_color;

	light = (t_light)light;
	light_color = vec3(0, 0, 0);
	light_color = vecPlusVec(light_color, hit_r.ambient);
	return (vecMin(vecMultVec(light_color, hit_r.albedo), vec3(1, 1, 1)));
}
