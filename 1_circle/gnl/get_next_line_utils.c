/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:36:00 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/17 12:54:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	if (!s)
		return (0);
	cnt = 0;
	while (*s != '\0')
	{
		s++;
		cnt++;
	}
	return (cnt);
}

char	*ft_strchr(const char *s, int c)
{
	size_t				i;
	size_t				len;
	const unsigned char	*str;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	str = (const unsigned char *)s;
	while (i < len)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}

t_list	*ft_lstfd(t_list **head, int fd)
{
	t_list	*pre;
	t_list	*cur;

	cur = *head;
	pre = NULL;
	while (cur)
	{
		pre = cur;
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	cur = malloc(sizeof(t_list));
	if (cur == NULL)
		return (NULL);
	cur->fd = fd;
	cur->backup = NULL;
	cur->next = NULL;
	if (!*head)
		*head = cur;
	if (pre)
		pre->next = cur;
	return (cur);
}
