/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:33:38 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 18:00:38 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// R, G, B 값을 하나의 int 값으로 만들어야 하는 경우.
int	writeColor(t_vec3 *pixelColor)
{
	int	t;

	t = 1; // 왜 1이지?
	return (t << 24 | (int)(255 * pixelColor->x) << 16 | (int)(255 * pixelColor->y) << 8 | (int)(255 * pixelColor->z));
}

int	createTrgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
