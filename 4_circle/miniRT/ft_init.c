/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:23:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/05 16:22:01 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "miniRT.h"

t_canvas	initCanvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspectRatio = (double)width / (double)height;
	return (canvas);
}

t_camera	initCamera(t_canvas *canvas, t_vec3 orig)
{
	t_camera	cam;
	double		focalLen;
	double		viewportHeight;

	viewportHeight = 2.0;
	focalLen = 1.0;
	cam.origPoint = orig;
	cam.viewportH = viewportHeight;
	cam.viewportW = viewportHeight * canvas->aspectRatio; // 화면 비율을 곱해서 구함.
	cam.focalLen = focalLen; // 보통 1로 고정해서 보여준다.
	cam.horizontal = vec3(cam.viewportW, 0, 0);
	cam.vertical = vec3(0, cam.viewportH, 0);
	cam.leftBottom = vecMinusVec(vecMinusVec(vecMinusVec(cam.origPoint, vecDivide(cam.horizontal, 2)), vecDivide(cam.vertical, 2)), vec3(0, 0, focalLen));
	return (cam);
}

t_sphere	makeSphere(t_vec3 center, double radius, t_vec3 albedo)
{
	t_sphere	sp;

	sp.center = center;
	sp.radius = radius;
	sp.radius2 = radius * radius;
	sp.albedo = albedo;
	return (sp);
}

t_light	makeLightPoint(t_vec3 light_orig, t_vec3 light_color, double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light)
	if (!light)
		return (NULL;)
	light->orig = light_orig;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

// t_scene	*initScene(void)
// {
// 	t_scene		*scene;
// 	light		*lights;
// 	t_sphere	*sp;
// 	double		ka; // 8.4 에서 설명

// 	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
// 	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
// 		return (NULL);
// 	scene->canvas = canvas(400, 300);
// 	scene->camera = camera(&scene->canvas, point3(0, 0, 0));
// 	// 구 오브젝트 추가
// 	image.sp = malloc(sizeof(t_sphere) * 3);
// 	if (image.sp == NULL)
// 		exit (0);
// 	image.sp[0] = makeSphere(point3(-1, 0, -5), 2, point3(0.5, 0, 0));
// 	image.sp[1] = makeSphere(point3(1, 0, -4), 2, point3(0, 0.5, 0));
// 	image.sp[2] = makeSphere(point3(0, 1000, -100), 999, point3(1, 1, 1));
// 	lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
// 	scene->light = lights;
// 	ka = 0.1; // 8.4 에서 설명
// 	scene->ambient = vmult(color(1,1,1), ka); // 8.4 에서 설명
// 	return (scene);
// }
