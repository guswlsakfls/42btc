/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:36:00 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/16 14:36:02 by hyujo            ###   ########.fr       */
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

t_list	*ft_lstnew(int fd)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->fd = fd;
	list->backup = NULL;
	list->next = NULL;
	return (list);
}

t_list	*ft_lstfd(t_list **head, int fd)
{
	t_list	*prev_lst;
	t_list	*cur_lst;

	cur_lst = *head;
	if (!*head)
	{
		*head = ft_lstnew(fd);
		return (*head);
	}
	while (cur_lst)
	{
		prev_lst = cur_lst;
		if ((cur_lst)->fd == fd)
			return (cur_lst);
		cur_lst = cur_lst->next;
	}
	cur_lst = ft_lstnew(fd);
	prev_lst->next = cur_lst;
	return (cur_lst);
}
