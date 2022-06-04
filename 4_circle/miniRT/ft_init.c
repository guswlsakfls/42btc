/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:23:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/04 19:08:58 by hyujo            ###   ########.fr       */
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
