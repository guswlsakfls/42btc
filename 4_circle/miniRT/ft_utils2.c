/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:36:53 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:36:53 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	if (!dst || !src)
		return (0);
	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

double	ft_atof(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1.0;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			dec_part = dec_part / 10 + ((double)(*str++ - '0') / 10);
	}
	return (sign * (int_part + dec_part));
}

void	free_split(char **str, size_t index)
{
	while (index--)
	{
		free(str[index]);
		str[index] = NULL;
	}
	free(str);
	str = NULL;
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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

static int	ft_isvalidchar(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || (c == '-') || (c == '+') || (c == '.')
		|| (c == ',') || (c == ' ') || (c == '\n'))
		return (1);
	return (0);
}

int	check_split(char **s)
{
	int	re;

	re = 0;
	while (s[re] != 0)
		re++;
	return (re);
}

void	info_line_split(t_info *info, int id)
{
	static int	info_qty[6] = {3, 4, 4, 4, 4, 6};
	int			i;
	// int			j;

	i = 0;
	while (info->line[i])
	{
		if (ft_isvalidchar(info->line[i]) == 0)
			exit(1);
		i++;
	}
	info->split = ft_split(info->line, ' ');
	if (check_split(info->split) != info_qty[id])
		exit(1);
}
