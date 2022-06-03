/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:25:52 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/01 17:08:40 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	ft_move_bottom(t_game *game)
{
	char	*ptr;
	int		i;

	ptr = ft_strchr(game->map->map, 'P');
	i = -1;
	while (++i < game->map->width)
		++ptr;
	if ((*ptr != '1' && *ptr != 'E')
		|| (*ptr != '1' && !(game->coin)))
	{
		if (*ptr == 'C')
			(game->coin)--;
		if (*ptr == 'E')
			game->flag = END;
		*ptr = 'P';
		ptr = ft_strchr(game->map->map, 'P');
		*ptr = '0';
		(game->player_move)++;
		printf("player_move : %d\n", game->player_move);
	}
	mlx_destroy_image(game->vars->mlx, game->sprites->player);
	game->sprites->player = ft_init_img(PLAYERDOWN,
			game->vars->mlx, game->sprites);
}

void	ft_move_up(t_game *game)
{
	char	*ptr;
	int		i;

	i = -1;
	ptr = ft_strchr(game->map->map, 'P');
	while (++i < game->map->width)
		--ptr;
	if ((*ptr != '1' && *ptr != 'E')
		|| (*ptr != '1' && !(game->coin)))
	{
		if (*ptr == 'C')
			(game->coin)--;
		if (*ptr == 'E')
			game->flag = END;
		*ptr = 'P';
		while (--i >= 0)
			++ptr;
		*ptr = '0';
		(game->player_move)++;
		printf("player_move : %d\n", game->player_move);
	}
	mlx_destroy_image(game->vars->mlx, game->sprites->player);
	game->sprites->player = ft_init_img(PLAYERUP,
			game->vars->mlx, game->sprites);
}

void	ft_move_right(t_game *game)
{
	char	*ptr;

	ptr = ft_strchr(game->map->map, 'P');
	if ((*(++ptr) != '1' && *ptr != 'E')
		|| (*ptr != '1' && !(game->coin)))
	{
		if (*ptr == 'C')
			(game->coin)--;
		if (*ptr == 'E')
			game->flag = END;
		*(--ptr) = '0';
		*(++ptr) = 'P';
		(game->player_move)++;
		printf("player_move : %d\n", game->player_move);
	}
	mlx_destroy_image(game->vars->mlx, game->sprites->player);
	game->sprites->player = ft_init_img(PLAYERRIGHT,
			game->vars->mlx, game->sprites);
}

void	ft_move_left(t_game *game)
{
	char	*ptr;

	ptr = ft_strchr(game->map->map, 'P');
	if ((*(--ptr) != '1' && *ptr != 'E')
		|| (*ptr != '1' && !(game->coin)))
	{
		if (*ptr == 'C')
			(game->coin)--;
		if (*ptr == 'E')
			game->flag = END;
		*(++ptr) = '0';
		*(--ptr) = 'P';
		(game->player_move)++;
		printf("player_move : %d\n", game->player_move);
	}
	mlx_destroy_image(game->vars->mlx, game->sprites->player);
	game->sprites->player = ft_init_img(PLAYERLEFT,
			game->vars->mlx, game->sprites);
}
