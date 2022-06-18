/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scha <scha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:33:38 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 21:46:56 by scha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	write_color(t_vec3 *pixelColor)
{
	int	t;

	t = 1;
	return (t << 24 | (int)(255 * pixelColor->x) << 16 |
		(int)(255 * pixelColor->y) << 8 | (int)(255 * pixelColor->z));
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx(t_vars *vars, t_image *image, t_canvas canvas)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, canvas.width,
			canvas.height, "miniRT");
	image->img = mlx_new_image(vars->mlx, canvas.width,
			canvas.height);
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
}

void	check_cam_normalize(t_camera *cam)
{
	if (cam->normalize.x == 0 && (cam->normalize.y == -1 || cam->normalize.y)
		&& cam->normalize.z == 0)
		cam->normalize.z += 0.001;
}

void	msg_exit(const char *msg)
{
	printf("%s error\n", msg);
	exit (1);
}
