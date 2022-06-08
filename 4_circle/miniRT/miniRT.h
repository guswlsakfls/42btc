/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:58:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/08 19:43:08 by hyujo            ###   ########.fr       */
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

# define BUFFER_SIZE 100

# define KEY_ESC 53

# define SP 0
# define LIGHT_POINT 1
# define EPSILON 1e-6 // 0.000001 // double 데이터 타입이 근사값이기 때문에 t의 값이 0에 가까운 값이 나올 때, tmin이 0이면 비교 시 hit 상황이 아닐 때도 hit로 판단하는 오차를 만들어 낼 수 있다.
# define LUMEN 5 // ㅇㅣ 값을 조절하여 장면의 밝기를 조절할 수 있다.

// 식별자 매크로
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

// typedef struct s_camera
// {
// 	t_vec3	origPoint; // 카메라 원점(위치) // cooordi_view
// 	double	viewportH; // 뷰포트 세로길이 
// 	double	viewportW; // 뷰포트 가로길이
// 	t_vec3	horizontal; // 수평길이 벡터	
// 	t_vec3	vertical; // 수직길이 벡터
// 	double	focalLen; // focal length
// 	t_vec3	leftBottom; // 왼쪽 아래 코너점
// }	t_camera;

typedef struct		s_amb
{
	double			ratio;
	t_vec3			color;
}					t_amb;

// scha
#include <stdbool.h>

typedef struct s_camera
{
	t_vec3	coordi_view;
	t_vec3	normalize;
	double		fov;
	t_vec3	origPoint; // 카메라 원점(위치) // cooordi_view
	double	viewportH; // 뷰포트 세로길이 
	double	viewportW; // 뷰포트 가로길이
	t_vec3	horizontal; // 수평길이 벡터	
	t_vec3	vertical; // 수직길이 벡터
	double	focalLen; // focal length
	t_vec3	leftBottom; // 왼쪽 아래 코너점
	struct s_camera	*next;
	struct s_camera	*prev;
}				t_camera;

typedef struct		s_elem
{
	t_vec3			pos;
	t_vec3			normal;
	t_vec3			color;
	double			ratio;
	double			diam;
	double			height;
	struct s_elem	*next;
}					t_elem;

typedef	struct s_canvas
{
	int		width;
	int		height;
	double	aspectRatio;
}	t_canvas;

typedef struct		s_info
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

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_image;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

typedef struct	s_rt
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

// scha

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
}	t_hitRecord;



// ft_init.c
void	init_canvas(t_canvas *canvas);
void	init_camera(t_camera *cam, t_canvas canvas, t_vec3 orig);


// calVec.c
t_vec3	vec3(double x, double y, double z);
t_vec3	point3(double x, double y, double z);
t_vec3	color3(double r, double g, double b);
void	vecSet(t_vec3 *vec, double x, double y, double z);
double	vecSquared(t_vec3 vec);
double	vecLength(t_vec3 vec);
t_vec3	vecPlusVec(t_vec3 vec, t_vec3 vec2);
t_vec3	vecPlus(t_vec3 vec, double x, double y, double z);
t_vec3	vecMinusVec(t_vec3 vec, t_vec3 vec2);
t_vec3	vecMinus(t_vec3 vec, double x, double y, double z);
t_vec3	vecMult(t_vec3 vec, double t);
t_vec3	vecMultVec(t_vec3 vec, t_vec3 vec2);
t_vec3	vecDivide(t_vec3 vec, double t);
double	vecDotVec(t_vec3 vec, t_vec3 vec2);
t_vec3	vecCrossVec(t_vec3 vec, t_vec3 vec2);
t_vec3	vecUnit(t_vec3 vec);
t_vec3	vecMin(t_vec3 vec1, t_vec3 vec2);
t_vec3	vecMax(t_vec3 vec, t_vec3 vec2);


// trace.c
t_ray	initRay(t_vec3 orig, t_vec3 dir);
t_vec3	rayAt(t_ray *ray, double t);
t_ray	rayPrimary(t_camera cam, double u, double v);
t_vec3	rayColor(t_ray *r, t_info info, t_rt *rt);
void	setFaceNormal(t_ray *ray, t_hitRecord *hit_record, t_elem sp, double root);


// utils_1.c
int		writeColor(t_vec3 *pixelColor);
int		createTrgb(int t, int r, int g, int b);

// figure
int			hitSphere(t_elem sp, t_ray *ray, t_hitRecord *hitRecord);
t_light		makeLightPoint(t_vec3 light_orig, t_vec3 light_color, double bright_ratio);
t_vec3		phongLightning(t_rt *rt, t_hitRecord *hit_record);
t_vec3		pointLightGet(t_rt *rt, t_elem *light, t_hitRecord *hit_record);
int			inShadow(t_info info, t_ray light_ray, double light_len);
t_vec3		reflect(t_vec3 v, t_vec3 n);

// scha

/*init*/
void	check_line(char* line, t_info *info);
void	init_info(char* file, t_info *info);
void	init_info2(t_rt *rt);

/*get*/
double	get_double(char *str);
double	get_ratio(char *str);
int		check_split(char **s);
t_vec3	get_vector(char *str);
t_vec3	get_normal(char *str);
t_vec3	get_color(char *str);
int		get_posint(char *str);
int		get_int(char *str);
void	get_light(t_elem *new, t_info *info);
void	get_sphere(t_elem *new, t_info *info);
void	get_plane(t_elem *new, t_info *info);
void	get_cylinder(t_elem *new, t_info *info);
void	get_amb(t_info *info);
void	get_camera(t_info *info);

void	info_line_split(t_info *info, int id);

/*utils*/
int		ft_atoi(const char *str);
double	ft_atof(const char *str);
void	free_split(char **str, size_t index);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strnldup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);
int		ft_isdigit(int c);
int		check_split(char **s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int		ft_str_isdouble(char *str);
bool	ft_str_isint(char *str);
// scha


#endif
