/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:08:51 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 21:31:06 by hyujo            ###   ########.fr       */
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

t_ray	rayPrimary(t_camera cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam.origPoint;
	ray.dir = vecUnit(vecMinusVec(vecPlusVec(vecPlusVec(cam.leftBottom,
						vecMult(cam.horizontal, u)), vecMult(cam.vertical, v)),
				cam.origPoint));
	return (ray);
}

int	hitObj(t_elem sp, t_ray *ray, t_hitRecord *hit_record)
{
	int	hit_result;

	hit_result = FALSE;
	hit_result = hitSphere(sp, ray, hit_record);
	return (hit_result);
}



int	hit(t_info info, t_ray *ray, t_hitRecord *hit_record)
{
	int			hit_anything;
	t_hitRecord	temp_record;

	temp_record = *hit_record;
	hit_anything = FALSE;
	while (info.sp)
	{
		if (hitObj(*info.sp, ray, &temp_record) == TRUE)
		{
			hit_anything = TRUE;
			temp_record.tmax = temp_record.t;
			*hit_record = temp_record;
			hit_record->color = info.sp->color;
		}
		info.sp = info.sp->next;
	}
	return (hit_anything);
}

// 광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴
t_vec3	rayColor(t_ray *r, t_info info, t_rt *rt)
{
	t_vec3		rgb;
	t_hitRecord	hit_record;

	hit_record.tmin = EPSILON;
	hit_record.tmax = INFINITY;
	if (hit(info, r, &hit_record) == TRUE)
	{
		rt->color = hit_record.color;
		rgb = phongLightning(rt);
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

int	hitSphere(t_elem sp, t_ray *ray, t_hitRecord *hit_record)
{
	// 여기 변수 줄여야함
	t_vec3	oc; // 구 가운데 부터 광선 까지 거리
	double	a;
	double	b;
	double	c;
	double	discri; // 판별식
	double	root;

	oc = vecMinusVec(ray->orig, sp.pos); // A-C (광선원점 - 구의 원점)
	a = vecDotVec(ray->dir, ray->dir); //(b * b)t^2
	b = 2.0 * vecDotVec(oc, ray->dir); // 2*b*(A-C)*t
	c = vecDotVec(oc, oc) - pow((double)(sp.diam / 2), 2); // (A-C) * (A-C) -r^2
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

void	setFaceNormal(t_ray *ray, t_hitRecord *hit_record, t_elem sp, double root)
{
	hit_record->t = root;
	hit_record->p = rayAt(ray, root);
	hit_record->normal = vecDivide(vecMinusVec(hit_record->p, sp.pos), (double)sp.diam / 2); // 이거 뭐 나타내는거?
	hit_record->albedo = vec3(0.5, 0.5, 0.5); // 반사율
	if (vecDotVec(ray->dir, hit_record->normal) > 0.0) // ray is inside
	{
		hit_record->normal = vecMult(hit_record->normal, -1);
		hit_record->front = FALSE;
	}
	else // ray is outside
		hit_record->front = TRUE;
}

t_vec3	phongLightning(t_rt *rt)
{
	t_vec3	light_color;
	t_elem	*lights;

	light_color = vec3(0, 0, 0);
	lights = rt->info.light;
	// while (lights)
	// {
	// 	if (lights->type == LIGHT_POINT)
	// 		light_color = vecPlusVec(light_color, pointLightGet(rt, lights->element));
	// 	lights = lights->next;
	// }
	light_color = vecPlusVec(light_color, rt->ambient);
	return (vecMin(vecMultVec(light_color, rt->albedo), rt->color));
	// 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}

t_vec3	pointLightGet(t_rt *rt, t_light *light)
{
	t_vec3	diffuse;
	t_vec3	light_dir;
	t_vec3	specular;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	t_ray	light_ray;
	double	light_len;
	double	kd;
	double	spec;
	double	ksn;
	double	ks;
	double	brightness;

	light_dir = vecMinusVec(light->orig, rt->hit_record.p);
	light_len = vecLength(light_dir);
	light_ray = initRay(vecPlus(re->hit_record.p, vecMult(re->hit_record.normal, EPSILON)), light_dir);
	if (inShadow(rt, light_ray, light_len))
		return (vec3(0, 0, 0));
	light_dir = vecUnit(light_dir);
	// cos 은 0값이 90도 일 때 0이고, 각이 둔각이면 음수가 되므로 0.0보다 작은 경우 0.0으로 대체한다.
	kd = vecMax(vecDotvec(rt->hit_record.normal, light_dir, 0.0));
	diffuse = vecMult(light->light_color, kd);
	// specular
	view_dir = vecUnit(vecMult(rt->ray.dir, -1));
	reflect_dir = reflect(vecMult(light_dir, -1), re->hit_record.normal);
	ksn = 64; // shininess value
	ks = 0.5; // specular strength
	spec = pow(vecMax(vecDot(view_dir, reflect_dir), 0.0), ksn);
	specular = vecMult(vecMult(light->light_color, ks), spec);
	brightness = light->bright_ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
	return (vecMult(vecPlus(vecPlus(ambient, diffuse), specular), brightness));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	// v - 2 * dot(v, n) * n;
	return (vecMinus(v, vecMult(n, vecDotVec(v, n) * 2)));
}

int	inShadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hitRecord	hitRecord;

	hitRecord.tmin = 0;
	hitRecord.tmax = light_len;
	if (hit(objs, &light_ray, &hitRecord))
		return (TRUE);
	return (FALSE);
}
