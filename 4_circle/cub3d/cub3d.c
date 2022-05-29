/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:59:17 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/01 17:35:57 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "so_long.h"

void	ft_print_error(int num)
{
	if (num == 0)
		printf("ERROR\nargc\n");
	else if (num == 1)
		printf("ERROR\nfile name\n");
	else if (num == 2)
		printf("ERROR\nfile open\n");
	else if (num == 3)
		printf("ERROR\nwin\n");
	else if (num == 4)
		printf("ERROR\nimg\n");
	else if (num == 5)
		printf("ERROR\nnot rectangular\n");
	else if (num == 6)
		printf("ERROR\nclose/surrounded map\n");
	else if (num == 7)
		printf("ERROR\nat least one exit, collectible and starting position\n");
	else if (num == 8)
		printf("ERROR\nthe player\n");
	else if (num == 9)
		printf("ERROR\nvalid map\n");
	else if (num == 10)
		printf("ERROR\nmlx_init\n");
	else if (num == 11)
		printf("ERROR\nmalloc\n");
	exit(1);
}

void	ft_check_arg(int ac, char *map_file)
{
	if (ac != 2)
		ft_print_error(0);
	else if (ft_strnstr(map_file, ".ber", ft_strlen(map_file)) == NULL)
		ft_print_error(1);
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
	ft_print_map(game);
	return (0);
}

int	ft_exit_hook(void)
{
	exit(0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	ft_check_arg(ac, av[1]);
	game = malloc(sizeof(t_game));
	if (!game)
		ft_print_error(11);
	ft_parsing_map(game, av[1]);
	ft_init_game(game);
	ft_init_sprite(game->vars, game->sprites);
	ft_print_map(game);
	mlx_key_hook(game->vars->win, &ft_key_hook, game);
	mlx_hook(game->vars->win, 17, 0, ft_exit_hook, game);
	mlx_loop(game->vars->mlx);
	return (0);
}
