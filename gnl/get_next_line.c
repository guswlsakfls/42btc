/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:16:16 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/12 19:20:32 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_listnew(t_list **head, int fd)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->fd = fd;
	list->backup = NULL;
	list->data = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (list->data == NULL)
		return (NULL);
	list->line = NULL;
	list->len = 0;
	list->offset = 1;
	list->next = NULL;
	*head = list;
	return (*head);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	if ((unsigned int)ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*list;

	while (head)
	{
		if (head->fd == fd)
			break ;
		head = head->next;
	}
	list = ft_listnew(&head, fd);
	while (list->offset != 0 && !ft_strchr(list->backup, '\n'))
	{
		list->offset = read(list->fd, list->data, BUFFER_SIZE);
		if (list->offset == -1)
		{
			free(list->data);
			return (NULL);
		}
		list->data[list->offset] = '\0';
		list->backup = ft_strjoin(list->backup, list->data);
	}
	printf("exbackup : %p\n%p\n", list->backup, ft_strchr(list->backup, '\n'));
	list->len = ft_strchr(list->backup, '\n') - list->backup;
	printf("len : %d\n", list->len);
	list->line = ft_substr(list->backup, 0, list->len + 1);
	printf("line : %s\n", list->line);
	list->backup = ft_strchr(list->backup, '\n') + 1;
	printf("afbackup : %s\n", list->backup);
	free(list->data);
	return (list->line);
}

int main()
{
	int fd;
	char *str;

	fd = open("text.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str[0] == '\0')
			break ;
		printf("str : %s\n", str);
	}
	close(fd);
	return (0);
}
