/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:59:17 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/13 14:36:50 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "miniRT.h"

int	ft_key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

void	myMlxPixelPut(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_exit_hook(void)
{
	exit(0);
}

void	init_mlx(t_vars *vars, t_image *image, t_canvas canvas)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, canvas.width, canvas.height, "miniRT");
	image->img = mlx_new_image(vars->mlx, canvas.width, canvas.height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
}
void	init_info2(t_rt *rt)
{
	init_canvas(&rt->canvas);
	init_camera(rt->info.camera, rt->canvas, point3(0, 0, 300));
	init_mlx(&rt->vars, &rt->image, rt->canvas);
}

int	main(int argc, char **argv)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_rt		rt;

	if (argc != 2)
		exit(1);
	init_info(argv[1], &rt.info);
	init_info2(&rt);
	j = rt.canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < rt.canvas.width)
		{
			u = (double)i / (rt.canvas.width - 1);
			v = (double)j / (rt.canvas.height - 1);
			rt.ray = rayPrimary(*rt.info.camera, u, v);
			rt.pixel_color = rayColor(&rt.ray, rt.info, &rt);
			myMlxPixelPut(&rt.image, i, j, writeColor(&rt.pixel_color));
			++i;
		}
		--j;
	}
	mlx_put_image_to_window(rt.vars.mlx, rt.vars.win, rt.image.img, 0, 0);
	// mlx_key_hook(vars.win, &ft_key_hook, &vars);
	// mlx_hook(win_ptr, 17, 0, ft_exit_hook, &);
	mlx_loop(rt.vars.mlx);
	return (0);
}
