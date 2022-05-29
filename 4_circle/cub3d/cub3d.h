/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:58:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/28 09:39:09 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <string.h>
# include <stdio.h>

# define BUFFER_SIZE 1
# define WALL "./Img/Wall.xpm"
# define COLLECT "./Img/Coin.xpm"
# define EXIT "./Img/Exit.xpm"
# define GROUND "./Img/Ground.xpm"

# define PLAYERRIGHT "./Img/PacManRight.xpm"
# define PLAYERLEFT "./Img/PacManLeft.xpm"
# define PLAYERUP "./Img/PacManUp.xpm"
# define PLAYERDOWN "./Img/PacManDown.xpm"

# define IMGSIZE 64

# define KEY_ESC 53

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define END 1

# define TOP 0
# define MID 1
# define BOT 2

typedef struct s_list
{
	int				fd;
	char			*backup;
	struct s_list	*next;
}	t_list;

typedef struct s_map
{
	char	*map;
	int		fd;
	int		width;
	int		height;
	int		col;
	int		row;
}	t_map;

typedef struct s_objs
{
	int		p;
	int		c;
	int		e;
}			t_objs;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_sprites
{
	void	*wall;
	void	*collect;
	void	*exit;
	void	*player;
	void	*ground;
	int		img_width;
	int		img_height;
}	t_sprites;

typedef struct s_game
{
	t_vars		*vars;
	t_map		*map;
	t_sprites	*sprites;
	t_objs		*objs;
	int			player_move;
	int			*coin;
	int			flag;
	char		*line;
}	t_game;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
t_list	*ft_lstnew(int fd);
t_list	*ft_lstfd(t_list **head, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_init_game(t_game *game);
void	*ft_init_img(char *img, void *mlx, t_sprites *sprite);
void	ft_init_sprite(t_vars *vars, t_sprites *sprite);
void	ft_print_error(int num);
void	ft_check_arg(int ac, char *map_file);
int		ft_key_hook(int keycode, t_game *game);
int		ft_exit_hook(void);
void	ft_move_bottom(t_game *game);
void	ft_move_up(t_game *game);
void	ft_move_right(t_game *game);
void	ft_move_left(t_game *game);
void	ft_put_img(t_game *game, void *sprite);
int		ft_print_map(t_game *game);
void	ft_check_map(int row, char *line, t_game *game);
void	ft_check_ecp(t_game *game);
void	ft_parsing_map(t_game *game, char *file);

#endif
