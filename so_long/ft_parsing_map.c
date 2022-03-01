/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:21:15 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/01 15:48:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	ft_check_map(int row, char *line, t_game *game)
{
	int	i;

	if (row == TOP || row == BOT)
	{
		if (game->map->width != (int)ft_strlen(line))
			ft_print_error(5);
		i = -1;
		while (++i < (int)ft_strlen(line))
		{
			if (line[i] != '1')
				ft_print_error(6);
		}
	}
	else if (row == MID)
	{
		if (game->map->width != (int)ft_strlen(line))
			ft_print_error(5);
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
			ft_print_error(6);
	}
}

void	ft_check_ecp(t_game *game)
{
	int	i;

	game->objs = malloc(1 * sizeof(t_objs));
	if (!(game->objs))
		return ;
	game->objs->e = 0;
	game->objs->c = 0;
	game->objs->p = 0;
	i = 0;
	while (game->map->map[i])
	{
		if (game->map->map[i] == 'E')
			game->objs->e++;
		else if (game->map->map[i] == 'C')
			game->objs->c++;
		else if (game->map->map[i] == 'P')
			game->objs->p++;
		else if (game->map->map[i] != '1' && game->map->map[i] != '0')
			ft_print_error(9);
		i++;
	}
	if (game->objs->p > 1)
		ft_print_error(8);
	if (!(game->objs->e) || !(game->objs->c) || !(game->objs->p))
		ft_print_error(7);
}

void	ft_parsing_map(t_game *game, char *file)
{
	game->map = malloc(sizeof(t_map));
	if (!(game->map))
		return ;
	game->map->fd = open(file, O_RDONLY);
	if (game->map->fd < 0)
		ft_print_error(2);
	game->map->map = get_next_line(game->map->fd);
	game->map->width = ft_strlen(game->map->map);
	ft_check_map(TOP, game->map->map, game);
	game->map->height = 1;
	while (1)
	{
		game->line = get_next_line(game->map->fd);
		if (!(game->line))
		{
			ft_check_map(BOT, &game->map->map[game->map->width
				* (game->map->height - 1)], game);
			break ;
		}
		ft_check_map(MID, game->line, game);
		game->map->height++;
		game->map->map = ft_strjoin(game->map->map, game->line);
		free(game->line);
	}
	ft_check_ecp(game);
}
