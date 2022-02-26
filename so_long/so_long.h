/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:58:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/26 17:33:04 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <string.h>
# include <stdio.h>

# define BUFFER_SIZE 1
# define GROUND "./textures/wall_s.xpm"

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

// mlx 구조체 mlx 포인터와 생성할 win 포인터를 가지고 있다.
typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_sprites
{
	void	*wall;
	void	*ground;
	void	*collect;
	void	*exit;
	void	**enemies;
	void	**player;
	int		img_width;
	int		img_height;
}			t_sprites;

typedef struct s_coin
{
	int		amount;
	int		amount_get;
}			t_coin;

typedef struct s_player
{
	int		player_left;
	int		player_right;
	int		player_up;
	int		player_down;
}			t_player;

//이미지의 정보를 나타내는 변수를 저장한 구조체
typedef struct s_game
{
	t_vars		*vars;
	t_map		*map;
	t_player	*player;
	t_coin		*coin;
	t_sprites	*sprite;
}	t_game;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
t_list	*ft_lstnew(int fd);
t_list	*ft_lstfd(t_list **head, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
