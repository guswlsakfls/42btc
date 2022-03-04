/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:23:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/01 17:28:07 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	ft_init_game(t_game *game)
{
	game->vars = malloc(1 * sizeof(t_vars));
	game->sprites = malloc(1 * sizeof(t_sprites));
	if (!(game->vars) || !(game->sprites))
		ft_print_error(11);
	game->player_move = 0;
	game->flag = 0;
	game->vars->mlx = mlx_init();
	if (!(game->vars->mlx))
		ft_print_error(10);
	game->vars->win = mlx_new_window(game->vars->mlx,
			game->map->width * IMGSIZE, game->map->height * IMGSIZE, "so_long");
	if (game->vars->win == NULL)
		ft_print_error(3);
}

void	*ft_init_img(char *img, void *mlx, t_sprites *sprite)
{
	void	*img_ptr;

	img_ptr = mlx_xpm_file_to_image(mlx, img,
			&sprite->img_width, &sprite->img_height);
	if (!img_ptr)
		ft_print_error(4);
	return (img_ptr);
}

void	ft_init_sprite(t_vars *vars, t_sprites *sprite)
{
	sprite->wall = ft_init_img(WALL, vars->mlx, sprite);
	sprite->collect = ft_init_img(COLLECT, vars->mlx, sprite);
	sprite->exit = ft_init_img(EXIT, vars->mlx, sprite);
	sprite->player = ft_init_img(PLAYERRIGHT, vars->mlx, sprite);
	sprite->ground = ft_init_img(GROUND, vars->mlx, sprite);
}
