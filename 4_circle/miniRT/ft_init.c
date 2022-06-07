/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:23:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 17:19:00 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "miniRT.h"

void	init_canvas(t_canvas *canvas)
{
	canvas->width = 1600;
	canvas->height = 900;
	canvas->aspectRatio = (double)canvas->width
		/ (double)canvas->height;
}

void	init_camera(t_camera *cam, t_canvas canvas, t_vec3 orig)
{
	double		focalLen;
	double		viewportHeight;

	viewportHeight = 2.0;
	focalLen = 1.0;
	cam->origPoint = orig;
	cam->viewportH = viewportHeight;
	cam->viewportW = viewportHeight * canvas.aspectRatio; // 화면 비율을 곱해서 구함.
	cam->focalLen = focalLen; // 보통 1로 고정해서 보여준다.
	cam->horizontal = vec3(cam->viewportW, 0, 0);
	cam->vertical = vec3(0, cam->viewportH, 0);
	cam->leftBottom = vecMinusVec(vecMinusVec(vecMinusVec(cam->origPoint, vecDivide(cam->horizontal, 2)), vecDivide(cam->vertical, 2)), vec3(0, 0, focalLen));
}

// t_sphere	makeSphere(t_vec3 center, double radius, t_vec3 albedo)
// {
// 	t_sphere	sp;

// 	sp.center = center;
// 	sp.radius = radius;
// 	sp.radius2 = radius * radius;
// 	sp.albedo = albedo;
// 	return (sp);
// }

// t_light	makeLightPoint(t_vec3 light_orig, t_vec3 light_color, double bright_ratio)
// {
// 	t_light	*light;

// 	light = (t_light *)malloc(sizeof(t_light)
// 	if (!light)
// 		return (NULL;)
// 	light->orig = light_orig;
// 	light->light_color = light_color;
// 	light->bright_ratio = bright_ratio;
// 	return (light);
// }

void	check_line(char* line, t_info *info)
{
	t_elem *new;

	if (ft_strncmp(line, "A ", 2) == 0)
		get_amb(info);
	else if (ft_strncmp(line, "C ", 2) == 0)
			get_camera(info);
	else
	{
		new = malloc(sizeof(t_elem));
		if (!new)
			exit(1);
		ft_bzero(new, 0);
		new->next = NULL;
		if (ft_strncmp(line, "L ", 2) == 0)
			get_light(new,info);
		else if (ft_strncmp(line, "sp", 2) == 0)
			get_sphere(new,info);
		else if (ft_strncmp(line, "pl", 2) == 0)
			get_plane(new,info);
		else if (ft_strncmp(line, "cy", 2) == 0)
			get_cylinder(new,info);
	}
}

void	init_info(char* file, t_info *info)
{
	int	fd;
	int	re;

	*info = (t_info) {0};
	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
		exit(1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(1);
	while ((re = get_next_line(fd, &(info->line)) > 0))
	{
		check_line(info->line, info);
		free(info->line);
		if (re == 0)
			break;
	}
	close(fd);
	if(info->qtys[0] == 0 || info->qtys[1] == 0 || info->qtys[2] == 0)
		exit(1);
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
