/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 01:02:48 by dha               #+#    #+#             */
/*   Updated: 2022/03/29 20:10:08 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *) s1;
	tmp_s2 = (unsigned char *) s2;
	if (n == 0)
		n = 2147483647;
	i = 0;
	while (i < n && tmp_s1[i] && tmp_s2[i])
	{
		if (tmp_s1[i] != tmp_s2[i])
			break ;
		i++;
	}
	return (tmp_s1[i] - tmp_s2[i]);
}
