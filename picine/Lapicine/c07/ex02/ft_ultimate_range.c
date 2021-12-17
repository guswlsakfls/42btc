/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:50:19 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/20 20:56:34 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	len;
	int	i;

	if (min >= max)
		return (0);
	len = max - min;
	range[0] = malloc(sizeof(int *) * len + 1);
	if (range == 0)
		return (-1);
	i = 0;
	while (i < len)
	{
		range[0][i] = min + i;
		i++;
	}
	return (i);
}
