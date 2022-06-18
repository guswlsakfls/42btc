/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scha <scha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:53:36 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/16 19:26:00 by scha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

int	ft_strlen(const char *s)
{
	int	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	check_normal(t_vec3 nor)
{
	if (nor.x > 1.0 || nor.x < -1.0)
		msg_exit("normallize vector ");
	if (nor.y > 1.0 || nor.y < -1.0)
		msg_exit("normallize vector ");
	if (nor.z > 1.0 || nor.z < -1.0)
		msg_exit("normallize vector ");
}
