/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:08:51 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/04 17:28:12 by hyujo            ###   ########.fr       */
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

int	hitObj(t_sphere sp, t_ray *ray, t_hitRecord *hit_record)
{
	int	hit_result;

	hit_result = FALSE;
	// if (world->type == sp) // 지금 타입이 뭔지.
		hit_result = hitSphere(sp, ray, hit_record);
	return (hit_result);
}

int	hit(t_sphere *sp, t_ray *ray, t_hitRecord *hit_record)
{
	int			hit_anything;
	t_hitRecord	temp_record;
	int	i;

	temp_record = *hit_record;
	hit_anything = FALSE;
	i = 0;
	while (i < 3) // 모든 도형이 들어있는 world 가 돌것이다.
	{
		if (hitObj(sp[i], ray, &temp_record) == TRUE)
		{
			hit_anything = TRUE;
			temp_record.tmax = temp_record.t;
			*hit_record = temp_record;
		}
		i++;
	}
	return (hit_anything);
}

// 광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴
t_vec3	rayColor(t_ray *r, t_sphere *sphere)
{
	t_vec3		rgb;
	t_vec3		tmp;
	t_vec3		n;
	t_hitRecord	hit_record;

	hit_record.tmin = 0;
	hit_record.tmax = INFINITY;
	if (hit(sphere, r, &hit_record) == TRUE)
	{
		// 구  그라데이션
		tmp = rayAt(r, hit_record.t);
		n = vecUnit(vec3(tmp.x - 0, tmp.y - 0, tmp.z - (-1)));
		rgb = vecMult(vec3(n.x + 1, n.y + 1, n.z + 1), 0.5);
		return (rgb);
	}
	else
	{
		// 단위 벡터가 -1 1 인데 음수가 들어오면 컬러에는 음수가 없기 때문에 아래와 같이 연산한다.
		hit_record.t = 0.5 * (r->dir.y + 1.0);
		// (1-t) * 흰색 + t * 하늘색
		rgb = vecPlusVec(vecMult(color3(1.0, 1.0, 1.0), (1.0 - hit_record.t)), vecMult(color3(0.5, 0.7, 1.0), hit_record.t));
		return (rgb);
	}
}

int	hitSphere(t_sphere sp, t_ray *ray, t_hitRecord *hit_record)
{
	// 여기 변수 줄여야함
	t_vec3	oc; // 구 가운데 부터 광선 까지 거리
	double	a;
	double	b;
	double	c;
	double	discri; // 판별식
	double	root;

	oc = vecMinusVec(ray->orig, sp.center); // A-C (광선원점 - 구의 원점)
	a = vecDotVec(ray->dir, ray->dir); //(b * b)t^2
	b = 2.0 * vecDotVec(oc, ray->dir); // 2*b*(A-C)*t
	c = vecDotVec(oc, oc) - sp.radius2; // (A-C) * (A-C) -r^2
	discri = b * b - 4 * a * c;
	if (discri < 0)
		return (FALSE);
	root = (-b - sqrt(discri)) / (2.0 * a);
	if (root < hit_record->tmin || hit_record->tmax < root)
	{
		root = (-b + sqrt(discri)) / (2.0 * a);
		if (root < hit_record->tmin || hit_record->tmax < root)
			return (-1);
	}
	setFaceNormal(ray, hit_record, sp, root);
	return (TRUE);
}

void	setFaceNormal(t_ray *ray, t_hitRecord *hit_record, t_sphere sp, double root)
{
	hit_record->t = root;
	hit_record->p = rayAt(ray, root);
	hit_record->normal = vecDivide(vecMinusVec(hit_record->p, sp.center), sp.radius); // 이거 뭐 나타내는거?
	if (vecDotVec(ray->dir, hit_record->normal) > 0.0) // ray is inside
	{
		hit_record->normal = vec3(-hit_record->normal.x,
				-hit_record->normal.y, -hit_record->normal.z);
		hit_record->front = FALSE;
	}
	else // ray is outside
		hit_record->front = TRUE;
}
