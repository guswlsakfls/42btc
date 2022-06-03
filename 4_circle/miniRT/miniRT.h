/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:58:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/03 15:01:33 by hyujo            ###   ########.fr       */
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

# define END 1

# define TOP 0
# define MID 1
# define BOT 2

// 식별자 매크로
# define FALSE 0
# define TURE 1

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

typedef struct s_light
{
	t_vec3	orig;
	t_vec3	lightColor;
	double	brightRatio;
}	t_light;

typedef struct s_hitRecord
{
	t_vec3	p;
	t_vec3	normal;
	double	tmin;
	double	tmax;
	double	t;
	int		frontFace;
	t_vec3	ambient; // 반사광 계수를 벡터화 시킨것.
	t_vec3	albedo;
}	t_hitRecord;

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


// trace.c
t_ray	initRay(t_vec3 orig, t_vec3 dir);
t_vec3	rayAt(t_ray *ray, double t);
t_ray	rayPrimary(t_camera *cam, double u, double v);
t_vec3	rayColor(t_ray *r, t_sphere *sphere);
t_vec3	phongLighting(t_light light, t_hitRecord hitR);


// utils_1.c
int		writeColor(int t, t_vec3 *pixelColor);
int		createTrgb(int t, int r, int g, int b);

// figure
t_sphere	makeSphere(t_vec3 center, double radius, t_vec3 albedo);
double		hitSphere(t_sphere *sp, t_ray *ray);

#endif
