/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scha <scha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:59:17 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 20:16:15 by scha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_key_hook(int keycode, t_rt *rt)
{
	t_camera	*temp;
	static int	qtys;
	int			i;

	i = 0;
	temp = rt->info.camera;
	if (keycode == 124 || keycode == 123)
	{
		if (keycode == 124)
			qtys += 1;
		else
			qtys -= 1;
		if (qtys == rt->info.qtys[1])
			qtys -= rt->info.qtys[1];
		else if (qtys < 0)
			qtys += rt->info.qtys[1];
		while (i++ != qtys)
			temp = temp->next;
		mlx_put_image_to_window(rt->vars.mlx,
			rt->vars.win, temp->image.img, 0, 0);
	}
	if (keycode == 53)
		exit(0);
	return (0);
}

void	init_image(t_rt *rt)
{
	t_camera	*temp;

	temp = rt->info.camera;
	while (temp)
	{
		temp->image.img = mlx_new_image(rt->vars.mlx,
				rt->canvas.width, rt->canvas.height);
		temp->image.addr = mlx_get_data_addr(temp->image.img,
				&temp->image.bpp, &temp->image.line_length,
				&temp->image.endian);
		temp = temp->next;
	}
}

void	init_info2(t_rt *rt)
{
	init_canvas(&rt->canvas);
	init_camera(rt->info.camera, rt->canvas, rt->info);
	init_mlx(&rt->vars, &rt->image, rt->canvas);
	init_image(rt);
}

void	start_ray(t_rt *rt, t_camera *temp, int qtys)
{
	int		i;
	int		j;
	double	u;
	double	v;

	while (qtys--)
	{
		j = rt->canvas.height - 1;
		while (j >= 0)
		{
			i = 0;
			while (i < rt->canvas.width)
			{
				u = (double)i / (rt->canvas.width - 1);
				v = (double)j / (rt->canvas.height - 1);
				rt->ray = ray_primary(*temp, u, v);
				rt->pixel_color = ray_color(&rt->ray, rt->info, rt);
				my_mlx_pixel_put(&temp->image, i, j,
					write_color(&rt->pixel_color));
				i++;
			}
			--j;
		}
		temp = temp->next;
	}
}

int	main(int argc, char **argv)
{
	t_rt		rt;

	if (argc != 2)
		msg_exit("argument ");
	init_info(argv[1], &rt.info);
	init_info2(&rt);
	start_ray(&rt, rt.info.camera, rt.info.qtys[1]);
	mlx_put_image_to_window(rt.vars.mlx, rt.vars.win,
		rt.info.camera->image.img, 0, 0);
	mlx_key_hook(rt.vars.win, ft_key_hook, &rt);
	mlx_hook(rt.vars.win, 17, 0, ft_exit_hook, 0);
	mlx_loop(rt.vars.mlx);
	return (0);
}
