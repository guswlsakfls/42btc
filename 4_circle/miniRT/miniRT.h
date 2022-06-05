/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:58:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/05 17:14:41 by hyujo            ###   ########.fr       */
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

# define BUFFER_SIZE 1

# define IMGSIZE 64

# define KEY_ESC 53

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define SP 0
# define LIGHT_POINT 1
# define EPSILON 1e-6 // 0.000001 // double 데이터 타입이 근사값이기 때문에 t의 값이 0에 가까운 값이 나올 때, tmin이 0이면 비교 시 hit 상황이 아닐 때도 hit로 판단하는 오차를 만들어 낼 수 있다.

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

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	double	radius2;
	t_vec3	albedo;
}	t_sphere;

typedef struct s_light
{
	t_vec3	orig;
	t_vec3	light_color;
	double	bright_ratio;
}	t_light;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_sphere	*sp;
}	t_data;

typedef struct s_camera
{
	t_vec3	origPoint; // 카메라 원점(위치)
	double	viewportH; // 뷰포트 세로길이
	double	viewportW; // 뷰포트 가로길이
	t_vec3	horizontal; // 수평길이 벡터	
	t_vec3	vertical; // 수직길이 벡터
	double	focalLen; // focal length
	t_vec3	leftBottom; // 왼쪽 아래 코너점
}	t_camera;

typedef	struct s_canvas
{
	int		width;
	int		height;
	double	aspectRatio; // 종횡비
}	t_canvas;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray;

typedef struct s_hitRecord
{
	t_vec3	p;
	t_vec3	normal;
	double	tmin;
	double	tmax;
	double	t;
	int		front;
	t_vec3	albedo;
}	t_hitRecord;

typedef struct s_rt
{
	t_sphere		*sp;
	t_light			*light;
	t_vec3			ambient;
}	t_rt;

// typedef struct s_info
// {
// 	t_canvas		canvas;
// 	t_camera		camera;
// 	t_sphere		*sp;
// 	t_light			*light;
// 	t_vec3			ambient;
// 	t_ray			ray;
// 	t_hit_record	rec;
// }	t_scene;

// ft_init.c
t_canvas	initCanvas(int width, int height);
t_camera	initCamera(t_canvas *canvas, t_vec3 orig);


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
t_ray	rayPrimary(t_camera *cam, double u, double v);
t_vec3	rayColor(t_ray *r, t_sphere *sphere);
void	setFaceNormal(t_ray *ray, t_hitRecord *hit_record, t_sphere sp, double root);


// utils_1.c
int		writeColor(int t, t_vec3 *pixelColor);
int		createTrgb(int t, int r, int g, int b);

// figure
t_sphere	makeSphere(t_vec3 center, double radius, t_vec3 albedo);
int			hitSphere(t_sphere sp, t_ray *ray, t_hitRecord *hitRecord);
t_light		makeLightPoint(t_vec3 light_orig, t_vec3 light_color, double bright_ratio);
t_vec3		phongLightning(t_rt *rt)
t_vec3		pointLightGet(t_rt *rt, t_light *light)

#endif
