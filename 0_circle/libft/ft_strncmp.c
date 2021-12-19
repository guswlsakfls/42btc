/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:42:26 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/02 14:22:46 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cmp_s1;
	const unsigned char	*cmp_s2;

	cmp_s1 = (const unsigned char *)s1;
	cmp_s2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (cmp_s1[i] && cmp_s2[i] && i + 1 < n)
	{
		if (cmp_s1[i] != cmp_s2[i])
			return (cmp_s1[i] - cmp_s2[i]);
		i++;
	}
	return (cmp_s1[i] - cmp_s2[i]);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	printf("%d\n", ft_strncmp("test\200", "test\0", 6));
// 	printf("%d\n", strncmp("test\200", "test\0", 6));
// }
