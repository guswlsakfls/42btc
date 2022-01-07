/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:19:15 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/20 13:44:25 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	i;
	int	len;
	int	*range;

	if (min >= max)
		return (NULL);
	len = max - min;
	range = malloc(sizeof(int) * len + 1);
	i = 0;
	while (i < len)
	{
		range[i] = min + i;
		i++;
	}
	return (range);
}
