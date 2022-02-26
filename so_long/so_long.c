/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:59:17 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/26 20:18:55 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	ft_print_error(int num)
{
	if (num == 0)
		printf("ERROR\nargc error\n");
	else if (num == 1)
		printf("ERROR\nfile name error\n");
	else if (num == 2)
		printf("ERROR\nmap error\n");
	else if (num == 3)
		printf("ERROR\nwin error\n");
	exit(1);
}

void	ft_put_img(t_game *game, void *sprite)
{
	mlx_put_image_to_window (game->vars->mlx, game->vars->win, sprite,
		64 * game->map->col,
		64 * game->map->row);
}

void	ft_select_sprite(char sp_num, t_game *game)
{
	if (sp_num == '1')
		ft_put_img(game, game->sprite->ground);
}

void	*ft_init_img(char *img, void *mlx, t_sprites *sprite)
{
	void	*img_ptr;

	img_ptr = mlx_xpm_file_to_image(mlx, img,
			&sprite->img_width, &sprite->img_height);
	return (img_ptr);
}

void	ft_init_sprite(t_vars *vars, t_sprites *sprite)
{
	sprite->ground = ft_init_img(GROUND, vars->mlx, sprite);
}

int	ft_print_map(t_game *game)
{
	game->map->row = 0;
	// game->coin->amount = 0;
	while (game->map->row < game->map->height)
	{
		game->map->col = 0;
		while (game->map->col < game->map->width)
		{
			ft_select_sprite(game->map->map[game->map->row
				* game->map->width + game->map->col], game);
			game->map->col++;
		}
		game->map->row++;
	}
	return (0);
}

int	main_loop(t_game *game)
{
	ft_print_map(game);
	return (0);
}

void	ft_parsing_map(t_game *game, char *file)
{
	char	*line;
	char	*tmp_map;

	game->map = malloc(sizeof(t_map));
	game->map->fd = open(file, O_RDONLY);
	if (game->map->fd < 0)
		ft_print_error(2);
	tmp_map = get_next_line(game->map->fd);
	game->map->width = ft_strlen(tmp_map);
	game->map->height = 1;
	while (1)
	{
		line = get_next_line(game->map->fd);
		if (!line)
			break ;
		game->map->height++;
		tmp_map = ft_strjoin(tmp_map, line);
		free(line);
	}
	game->map->map = tmp_map;
	tmp_map = NULL;
}

void	ft_check_arg(int ac, char *av)
{
	if (ac != 2)
		ft_print_error(0);
	else if (ft_strnstr(av, ".ber", ft_strlen(av)) == NULL)
		ft_print_error(1);
}

void	ft_init_game(t_game *game)
{
	char	*tmp_map;

	game->vars = malloc(1 * sizeof(t_vars));
	game->player = malloc(1 * sizeof(t_player));
	game->coin = malloc(1 * sizeof(t_coin));
	game->sprite = malloc(1 * sizeof(t_sprites));
	tmp_map = game->map->map;
	game->vars->mlx = mlx_init();
	game->vars->win = mlx_new_window(game->vars->mlx,
			game->map->width * 64, game->map->height * 64, "so_long");
	if (game->vars->win == NULL)
		ft_print_error(3);
	game->map->map = tmp_map;
}

int main(int ac, char **av)
{
	t_game	*game;

	ft_check_arg(ac, av[1]);
	game = malloc(sizeof(t_game));
	ft_parsing_map(game, av[1]);
	ft_init_game(game);
	ft_init_sprite(game->vars, game->sprite);
	mlx_loop_hook(game->vars->mlx, &main_loop, game);
	mlx_loop(game->vars->mlx);
	return (0);
}
