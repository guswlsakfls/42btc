/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:57:54 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/13 16:25:22 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char				*str_trim;
	size_t				front;
	size_t				back;

	if (!s1 || !set)
		return (ft_strdup(""));
	front = 0;
	back = ft_strlen(s1);
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (back > front && ft_strchr(set, s1[back]))
		back--;
	if (back == front)
		return (ft_strdup(""));
	str_trim = malloc(sizeof(char) * back - front + 2);
	if (!str_trim)
		return (0);
	ft_strlcpy(str_trim, s1 + front, back - front + 2);
	return (str_trim);
}
