/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:23:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/17 16:28:43 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_canvas(t_canvas *canvas)
{
	canvas->width = 1600;
	canvas->height = 900;
	canvas->aspect_ratio = (double)canvas->width
		/ (double)canvas->height;
}

void	init_camera(t_camera *cam, t_canvas canvas, t_info info)
{
	double		viewport_height;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;

	while (info.qtys[1] != 0)
	{
		check_cam_normalize(cam);
		w = vec_unit(vec_mult_vec(cam->normalize, vec3(-1, -1, -1)));
		u = vec_unit(vec_cross_vec(vec3(0, 1, 0), w));
		v = vec_cross_vec(u, w);
		viewport_height = 2 * cam->fov;
		cam->orig_point = cam->coordi_view;
		cam->viewport_h = viewport_height;
		cam->viewport_w = viewport_height * canvas.aspect_ratio;
		cam->focal_len = 2.0;
		cam->horizontal = vec_mult(u, cam->viewport_w);
		cam->vertical = vec_mult(v, cam->viewport_h);
		cam->left_bottom = vec_minus_vec(vec_minus_vec(vec_minus_vec(
						cam->orig_point, vec_divide(cam->horizontal, 2)),
					vec_divide(cam->vertical, 2)), w);
		cam = cam->next;
		info.qtys[1] -= 1;
	}
}

void	check_line(char *line, t_info *info)
{
	t_elem	*new;

	if (ft_strncmp(line, "A ", 2) == 0)
		get_amb(info);
	else if (ft_strncmp(line, "C ", 2) == 0)
		get_camera(info);
	else
	{
		new = malloc(sizeof(t_elem));
		if (!new)
			msg_exit("malloc ");
		ft_bzero(new, 0);
		new->next = NULL;
		if (ft_strncmp(line, "L ", 2) == 0)
			get_light(new, info);
		else if (ft_strncmp(line, "sp ", 3) == 0)
			get_sphere(new, info);
		else if (ft_strncmp(line, "pl ", 3) == 0)
			get_plane(new, info);
		else if (ft_strncmp(line, "cy ", 3) == 0)
			get_cylinder(new, info);
		else
			free(new);
	}
}

static void	line_replace(char *line)
{
	if (!(line) || *line == '\0')
		return ;
	while (*line != '\0')
	{
		if (*line == '\t')
			*line = ' ';
		line++;
	}
}

void	init_info(char *file, t_info *info)
{
	int	fd;

	*info = (t_info){0};
	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
		msg_exit("file name ");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		msg_exit("fd ");
	while (1)
	{
		info->line = get_next_line(fd);
		if (info->line)
		{
			line_replace(info->line);
			check_line(info->line, info);
			free(info->line);
		}
		if (!(info->line))
			break ;
	}
	close(fd);
	if (info->qtys[0] == 0 || info->qtys[1] == 0 || info->qtys[2] == 0)
		msg_exit("input ");
}
