/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:59:17 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/27 15:56:12 by hyujo            ###   ########.fr       */
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
	else if (num == 4)
		printf("ERROR\nimg error\n");
	exit(1);
}

void	ft_put_img(t_game *game, void *sprite)
{
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, sprite,
		64 * game->map->col, 64 * game->map->row);
}

void	ft_select_sprite(char sp_num, t_game *game)
{
	if (sp_num == '1')
		ft_put_img(game, game->sprite->wall);
	if (sp_num == '0')
		ft_put_img(game, game->sprite->ground);
	else if (sp_num == 'C')
	{
		game->coin->amount++;
		ft_put_img(game, game->sprite->collect);
	}
	else if (sp_num == 'E')
		ft_put_img(game, game->sprite->exit);
	else if (sp_num == 'P')
		ft_put_img(game, game->sprite->player);
}

void	*ft_init_img(char *img, void *mlx, t_sprites *sprite)
{
	void	*img_ptr;

	img_ptr = mlx_xpm_file_to_image(mlx, img,
			&sprite->img_width, &sprite->img_height);
	if (img_ptr == 0)
		ft_print_error(4);
	return (img_ptr);
}

void	ft_init_sprite(t_vars *vars, t_sprites *sprite)
{
	sprite->wall = ft_init_img(WALL, vars->mlx, sprite);
	sprite->collect = ft_init_img(COLLECT, vars->mlx, sprite);
	sprite->exit = ft_init_img(EXIT, vars->mlx, sprite);
	sprite->player = ft_init_img(PLAYER, vars->mlx, sprite);
	sprite->ground = ft_init_img(GROUND, vars->mlx, sprite);
}

int	ft_print_map(t_game *game)
{
	game->coin->amount = 0;
	game->map->row = 0;
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
	if (!game->vars || !game->player || !game->coin || !game->sprite)
		return ;
	game->player->player_move = 0;
	game->flag = 0;
	tmp_map = game->map->map;
	game->vars->mlx = mlx_init();
	game->vars->win = mlx_new_window(game->vars->mlx,
			game->map->width * 64, game->map->height * 64, "so_long");
	if (game->vars->win == NULL)
		ft_print_error(3);
	game->map->map = tmp_map;
}

void	ft_move_bottom(t_game *game)
{
	char	*ptr;
	int		i;

	ptr = ft_strchr(game->map->map, 'P');
	i = -1;
	while (++i < game->map->width)
		++ptr;
	if ((*ptr != '1' && *ptr != 'E')
		|| (*ptr != '1' && !game->coin->amount))
	{
		if (*ptr == 'C')
			game->coin->amount--;
		if (*ptr == 'E')
			game->flag = END;
		*ptr = 'P';
		ptr = ft_strchr(game->map->map, 'P');
		*ptr = '0';
		game->player->player_move += 1;
		printf("player_move : %d\n", game->player->player_move);
	}
	// mlx_destroy_image(game->vars->mlx, game->sprite->player);
	// game->sprite->player = ft_init_img(PLAYER, game->vars->mlx, game->sprite);
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
		|| (*ptr != '1' && !game->coin->amount))
	{
		if (*ptr == 'C')
			game->coin->amount--;
		if (*ptr == 'E')
			game->flag = END;
		*ptr = 'P';
		while (--i >= 0)
			++ptr;
		*ptr = '0';
		game->player->player_move += 1;
		printf("player_move : %d\n", game->player->player_move);
	}
	// mlx_destroy_image(game->vars->mlx, game->sprite->player);
	// game->sprite->player = ft_init_img(PLAYER, game->vars->mlx, game->sprite);
}

void	ft_move_right(t_game *game)
{
	char	*ptr;

	ptr = ft_strchr(game->map->map, 'P');
	if ((*(++ptr) != '1' && *ptr != 'E')
		|| (*ptr != '1' && !game->coin->amount))
	{
		if (*ptr == 'C')
			game->coin->amount--;
		if (*ptr == 'E')
			game->flag = END;
		*(--ptr) = '0';
		*(++ptr) = 'P';
		game->player->player_move += 1;
		printf("player_move : %d\n", game->player->player_move);
	}
	// mlx_destroy_image(game->vars->mlx, game->sprite->player);
	// game->sprite->player = ft_init_img(PLAYER, game->vars->mlx, game->sprite);
}

void	ft_move_left(t_game *game)
{
	char	*ptr;

	ptr = ft_strchr(game->map->map, 'P');
	if ((*(--ptr) != '1' && *ptr != 'E')
		|| (*ptr != '1' && !game->coin->amount))
	{
		if (*ptr == 'C')
			game->coin->amount--;
		if (*ptr == 'E')
			game->flag = END;
		*(++ptr) = '0';
		*(--ptr) = 'P';
		game->player->player_move += 1;
		printf("player_move : %d\n", game->player->player_move);
	}
	// mlx_destroy_image(game->vars->mlx, game->sprite->player);
	// game->sprite->player = ft_init_img(PLAYER, game->vars->mlx, game->sprite);
}

int	ft_main_loop(t_game *game)
{
	ft_print_map(game);
	return (0);
}

int	ft_key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_S)
		ft_move_bottom(game);
	if (keycode == KEY_W)
		ft_move_up(game);
	if (keycode == KEY_D)
		ft_move_right(game);
	if (keycode == KEY_A)
		ft_move_left(game);
	if (game->flag == END)
		exit(1);
	return (0);
}

int main(int ac, char **av)
{
	t_game	*game;

	ft_check_arg(ac, av[1]);
	game = malloc(sizeof(t_game));
	ft_parsing_map(game, av[1]);
	ft_init_game(game);
	ft_init_sprite(game->vars, game->sprite);
	mlx_key_hook(game->vars->win, &ft_key_hook, game);
	mlx_loop_hook(game->vars->mlx, &ft_main_loop, game);
	mlx_loop(game->vars->mlx);
	return (0);
}
