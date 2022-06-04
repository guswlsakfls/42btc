/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:59:17 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/04 17:32:10 by hyujo            ###   ########.fr       */
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

void	myMlxPixelPut(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_exit_hook(void)
{
	exit(0);
}

int	main()
{
	t_data		image;
	t_vars		vars;
	int			i;
	int			j;
	double		u;
	double		v;
	t_vec3		pixelColor;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;
	int			t;

	t = 1;
	//Scene setting;
	canv = initCanvas(1600, 900);
	cam = initCamera(&canv, point3(0, 0, 0));

	// mlx 초기화
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, canv.width, canv.height, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, canv.width, canv.height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	image.sp = malloc(sizeof(t_sphere) * 4);
	if (image.sp == NULL)
		exit (0);
	image.sp[0] = makeSphere(point3(-1, 0, -5), 2, point3(0.5, 0, 0));
	image.sp[1] = makeSphere(point3(1, 0, -4), 2, point3(0, 0.5, 0));
	image.sp[2] = makeSphere(point3(0, 1000, -100), 999, point3(1, 1, 1));
	// 랜더링
	// P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			ray = rayPrimary(&cam, u, v);
			pixelColor = rayColor(&ray, image.sp);
			myMlxPixelPut(&image, i, j, writeColor(t, &pixelColor));
			++i;
		}
		--j;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	// mlx_key_hook(vars.win, &ft_key_hook, &vars);
	// mlx_hook(win_ptr, 17, 0, ft_exit_hook, &);
	mlx_loop(vars.mlx);
	free(image.sp);
	return (0);
}
