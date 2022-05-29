/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:24:51 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/01 16:47:43 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	ft_put_img(t_game *game, void *sprite)
{
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, sprite,
		64 * game->map->col, 64 * game->map->row);
}

void	ft_select_sprite(char sp_num, t_game *game)
{
	if (sp_num == 'C')
	{
		game->coin++;
		ft_put_img(game, game->sprites->collect);
	}
	else if (sp_num == 'E')
		ft_put_img(game, game->sprites->exit);
	else if (sp_num == 'P')
		ft_put_img(game, game->sprites->player);
}

int	ft_print_map(t_game *game)
{
	game->coin = 0;
	game->map->row = 0;
	while (game->map->row < game->map->height)
	{
		game->map->col = 0;
		while (game->map->col < game->map->width)
		{
			if (game->map->map[game->map->row
					* game->map->width + game->map->col] == '1')
				ft_put_img(game, game->sprites->wall);
			else
			{
				ft_put_img(game, game->sprites->ground);
				ft_select_sprite(game->map->map[game->map->row
					* game->map->width + game->map->col], game);
			}
			game->map->col++;
		}
		game->map->row++;
	}
	return (0);
}
