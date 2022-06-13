/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calVec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:40:02 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/13 17:29:07 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//벡터3 생성자
t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

//포인트3 생성자
t_vec3	point3(double x, double y, double z)
{
	t_vec3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

//색상3 생성자
t_vec3	color3(double r, double g, double b)
{
	t_vec3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

// 벡터 값 설정
void	vecSet(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

// 벡터 길이 제곱
double	vecSquared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// 벡터 길이
double	vecLength(t_vec3 vec)
{
	return (sqrt(vecSquared(vec)));
}

// 벡터합
t_vec3	vecPlusVec(t_vec3 vec, t_vec3 vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

// 벡터합2
t_vec3	vecPlus(t_vec3 vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

// 벡터차
t_vec3	vecMinusVec(t_vec3 vec, t_vec3 vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}

t_vec3	vecMinus(t_vec3 vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);
}

// 벡터 * 스칼라 곱연산
t_vec3	vecMult(t_vec3 vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

// 벡터 축 값끼리 곱연산
t_vec3	vecMultVec(t_vec3 vec, t_vec3 vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

// 벡터 스칼라 나누기
t_vec3	vecDivide(t_vec3 vec, double t)
{
	vec.x *= (double)(1 / t);
	vec.y *=  (double)(1 / t);
	vec.z *= (double)(1 / t);
	return (vec);
}

// 벡터 내적
double	vecDotVec(t_vec3 vec, t_vec3 vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

// 벡터 외적
t_vec3	vecCrossVec(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

// 단위 벡터
t_vec3	vecUnit(t_vec3 vec)
{
	double	len;

	len = vecLength(vec);
	if (len == 0)
	{
		printf("Error\n:Devider is 0");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

// 두 벡터의 원소를 비교하여 작은 값들만 반환 
t_vec3	vecMin(t_vec3 vec, t_vec3 vec2)
{
	if (vec.x > vec2.x)
		vec.x = vec2.x;
	if (vec.y > vec2.y)
		vec.y = vec2.y;
	if (vec.z > vec2.z)
		vec.z = vec2.z;
	return (vec);
}

t_vec3	vecMax(t_vec3 vec, t_vec3 vec2)
{
	if (vec.x < vec2.x)
		vec.x = vec2.x;
	if (vec.y < vec2.y)
		vec.y = vec2.y;
	if (vec.z < vec2.z)
		vec.z = vec2.z;
	return (vec);
}
