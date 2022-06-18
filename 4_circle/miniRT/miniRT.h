/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scha <scha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:58:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 21:18:34 by scha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include "./mlx/mlx.h"

# define BUFFER_SIZE 100

# define KEY_ESC 53

# define SP 0
# define LIGHT_POINT 1
# define EPSILON 1e-6
# define LUMEN 3
# define KSN 64
# define KS 0.5

# define FALSE 0
# define TRUE 1

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_amb
{
	double			ratio;
	t_vec3			color;
}					t_amb;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}	t_image;

typedef struct s_camera
{
	t_vec3			coordi_view;
	t_vec3			normalize;
	double			fov;
	t_vec3			orig_point;
	double			viewport_h;
	double			viewport_w;
	t_vec3			horizontal;
	t_vec3			vertical;
	double			focal_len;
	t_vec3			left_bottom;
	t_image			image;
	struct s_camera	*next;
	struct s_camera	*prev;
}				t_camera;

typedef struct s_elem
{
	t_vec3			pos;
	t_vec3			normal;
	t_vec3			color;
	double			ratio;
	double			diam;
	double			height;
	struct s_elem	*next;
}					t_elem;

typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
}	t_canvas;

typedef struct s_info
{
	char			*line;
	char			**split;
	t_amb			*amb;
	t_camera		*camera;
	t_elem			*light;
	t_elem			*sp;
	t_elem			*pl;
	t_elem			*cy;
	short int		qtys[6];
}					t_info;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

typedef struct s_rt
{
	t_vars		vars;
	t_canvas	canvas;
	t_image		image;
	t_ray		ray;
	t_info		info;
	t_vec3		pixel_color;
	t_vec3		albedo;
	t_vec3		ambient;
}				t_rt;

typedef struct s_light
{
	t_vec3	orig;
	t_vec3	light_color;
	double	bright_ratio;
}	t_light;

typedef struct s_hitRecord
{
	t_vec3	p;
	t_vec3	normal;
	double	tmin;
	double	tmax;
	double	t;
	int		front;
	t_vec3	color;
}	t_hitrecord;

typedef struct s_pl
{
	t_vec3	diffuse;
	t_vec3	light_dir;
	t_vec3	specular;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	t_ray	light_ray;
	double	light_len;
	double	kd;
	double	spec;
	double	ksn;
	double	ks;
	double	brightness;
}	t_pl;

typedef struct s_cy_side
{
	double	a;
	double	half_b;
	double	c;
	t_vec3	u;
	t_vec3	o;
	t_vec3	delta_p;
	double	r;
	double	discri;
	double	sqrtd;
	double	root;
	double	hit_height;
}	t_cy_side;

typedef struct s_list
{
	int				fd;
	char			*backup;
	struct s_list	*next;
}	t_list;

// ft_init.c
void			init_canvas(t_canvas *canvas);
void			init_camera(t_camera *cam, t_canvas canvas, t_info info);

// mlx
int				ft_exit_hook(void);
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);

// calVec.c
t_vec3			vec3(double x, double y, double z);
t_vec3			point3(double x, double y, double z);
t_vec3			color3(double r, double g, double b);
void			vec_set(t_vec3 *vec, double x, double y, double z);
double			vec_squared(t_vec3 vec);
double			vec_length(t_vec3 vec);
t_vec3			vec_plus_vec(t_vec3 vec, t_vec3 vec2);
t_vec3			vec_plus(t_vec3 vec, double x, double y, double z);
t_vec3			vec_minus_vec(t_vec3 vec, t_vec3 vec2);
t_vec3			vec_minus(t_vec3 vec, double x, double y, double z);
t_vec3			vec_mult(t_vec3 vec, double t);
t_vec3			vec_mult_vec(t_vec3 vec, t_vec3 vec2);
t_vec3			vec_divide(t_vec3 vec, double t);
double			vec_dot_vec(t_vec3 vec, t_vec3 vec2);
t_vec3			vec_cross_vec(t_vec3 vec, t_vec3 vec2);
t_vec3			vec_unit(t_vec3 vec);
t_vec3			vec_min(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec_max(t_vec3 vec, t_vec3 vec2);

// trace.c
t_ray			init_ray(t_vec3 orig, t_vec3 dir);
t_vec3			ray_at(t_ray *ray, double t);
t_ray			ray_primary(t_camera cam, double u, double v);
t_vec3			ray_color(t_ray *r, t_info info, t_rt *rt);
void			set_face_normal(t_ray *ray, t_hitrecord *record);
int				hit_plane(t_elem plane, t_ray *ray, t_hitrecord *hit_record);
void			cap_in_cylinder(t_elem *cy, t_info *info);
int				hit(t_info info, t_ray *ray, t_hitrecord *hit_record);

// cylinder.c
int				hit_cylinder(t_elem cylinder, t_ray ray, t_hitrecord *ret);

// utils_1.c
int				write_color(t_vec3 *pixelColor);
int				create_trgb(int t, int r, int g, int b);

// figure
int				hit_sphere(t_elem sp, t_ray *ray, t_hitrecord *hitRecord);
t_light			make_light_point(t_vec3 light_orig, t_vec3 light_color,
					double bright_ratio);
t_vec3			phong_lightning(t_rt *rt, t_hitrecord *hit_record);
t_vec3			point_light_get(t_rt *rt, t_elem *light,
					t_hitrecord *hit_record);
int				in_shadow(t_info info, t_ray light_ray, double light_len);
t_vec3			reflect(t_vec3 v, t_vec3 n);

/*init*/
void			check_line(char *line, t_info *info);
void			init_info(char *file, t_info *info);
void			init_info2(t_rt *rt);
void			init_mlx(t_vars *vars, t_image *image, t_canvas canvas);

/*get*/
double			get_double(char *str);
double			get_ratio(char *str);
int				check_split(char **s);
t_vec3			get_vector(char *str);
t_vec3			get_normal(char *str);
t_vec3			get_color(char *str);
int				get_posint(char *str);
int				get_int(char *str);
void			get_light(t_elem *new, t_info *info);
void			get_sphere(t_elem *new, t_info *info);
void			get_plane(t_elem *new, t_info *info);
void			get_cylinder(t_elem *new, t_info *info);
void			get_amb(t_info *info);
void			get_camera(t_info *info);

void			list_add_back_elem(t_elem *new, t_elem **lst);
void			info_line_split(t_info *info, int id);

/*utils*/
int				ft_atoi(const char *str);
double			ft_atof(const char *str);
void			free_split(char **str, size_t index);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen(const char *s);
char			**ft_split(const char *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_strnldup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
char			*get_next_line(int fd);
int				ft_isdigit(int c);
int				check_split(char **s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_list			*ft_lstfd(t_list **head, int fd);
void			msg_exit(const char *msg);
void			check_normal(t_vec3 nor);

int				ft_str_isdouble(char *str);
bool			ft_str_isint(char *str);
void			check_cam_normalize(t_camera *cam);

#endif
