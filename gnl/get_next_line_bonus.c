/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:16:16 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/16 19:36:50 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

void	ft_get_backup(t_list *list)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_size;

	read_size = 1;
	while (!ft_strchr(list->backup, '\n') && read_size != 0)
	{
		read_size = read(list->fd, buf, BUFFER_SIZE);
		if (read_size < 0)
		{
			list->backup = NULL;
			free(list);
			return ;
		}
		buf[read_size] = '\0';
		list->backup = ft_strjoin(list->backup, buf);
	}
}

char	*ft_get_line(t_list *list)
{
	int		i;
	char	*line;

	i = 0;
	if (!list->backup[i])
		return (NULL);
	while (list->backup[i] != '\n' && list->backup[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (list->backup[i] != '\n' && list->backup[i] != '\0')
	{
		line[i] = list->backup[i];
		i++;
	}
	if (list->backup[i] == '\n')
	{
		line[i] = list->backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	ft_left_backup(t_list *list)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (list->backup[i] != '\n' && list->backup[i] != '\0')
		i++;
	if (!list->backup[i])
	{
		free(list->backup);
		list->backup = NULL;
		return ;
	}
	tmp = malloc(sizeof(char) * (ft_strlen(list->backup) - i + 1));
	if (!tmp)
		return ;
	i++;
	j = -1;
	while (list->backup[i] != '\0')
	{
		tmp[++j] = list->backup[i++];
	}
	tmp[++j] = '\0';
	free(list->backup);
	list->backup = tmp;
}

t_list	*ft_find_next(t_list *head, t_list *list)
{
	t_list	*tmp;

	tmp = head;
	if (head == list)
	{
		head = head->next;
		free(list);
	}
	else
	{
		while (tmp->next != list)
			tmp = tmp->next;
		tmp->next = list->next;
		free(list);
		list = NULL;
	}
	return (head);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list = ft_lstfd(&head, fd);
	ft_get_backup(list);
	if (!list->backup)
	{
		list = NULL;
		return (NULL);
	}
	line = ft_get_line(list);
	ft_left_backup(list);
	if (!(list->backup))
		head = ft_find_next(head, list);
	return (line);
}
