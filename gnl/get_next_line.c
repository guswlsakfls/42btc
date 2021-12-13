/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:16:16 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/13 21:32:15 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
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

t_list	*ft_lstnew(int fd)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->fd = fd;
	list->backup = NULL;
	list->line = NULL;
	list->len = 0;
	list->offset = 1;
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

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*list;
	char			*temp;

	list = ft_lstfd(&head, fd);
	while (!ft_strchr(list->backup, '\n'))
	{
		list->offset = read(list->fd, list->data, BUFFER_SIZE);
		if (list->offset == -1)
		{
			if (list->backup != NULL)
			{
				free(list->backup);
				free(list->line);
			}
			free(list);
			return (NULL);
		}
		list->data[list->offset] = '\0';
		list->backup = ft_strjoin(list->backup, list->data);
		if (list->offset == 0)
		{
			free(list->backup);
			free(list);
			return (list->data);
		}
	}
	list->len = ft_strchr(list->backup, '\n') - list->backup;
	//printf("sub : %s\n", ft_substr(list->backup, 0, list->len + 1));
	list->line = ft_substr(list->backup, 0, list->len + 1);
	//printf("line : %p\n", list->line);
	list->backup = ft_strchr(list->backup, '\n') + 1;
	if (list->backup == NULL)
	{
		free(list->backup);
		free(list);
	}
	return (list->line);
}

int main()
{
	int fd[2];
	char *str;

	fd[0] = open("text.txt", O_RDONLY);
	//fd[1] = open("ttt.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd[0]);
		printf("str : %s\n", str);
		if (str[0] == '\0')
			break ;
		printf("str1 : %s", str);
		free(str);
		//str = get_next_line(fd[1]);
		//printf("str2 : %s", str);
		//free(str);
		printf("_______print________\n");
	}
	close(fd[0]);
	//close(fd[1]);
	system("leaks a.out");
	return (0);
}
