/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:16:16 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/14 14:49:26 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->fd = fd;
	list->backup = NULL;
	list->offset = 1;
	list->next = NULL;
	list->tmp_str = NULL;
	list->tmp_chr = 0;
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

char	*ft_rtn(t_list **list)
{
	char	*line;

	if ((*list)->offset == 0)
	{
		if ((*list)->backup != NULL)
		{
			line = ft_strdup((*list)->backup);
			free((*list)->backup);
			(*list)->backup = NULL;
			free((*list));
			(*list) = NULL;
			list = NULL;
			return (line);
		}
		else
		{
			free((*list)->backup);
			(*list)->backup = NULL;
			free(*list);
			*list = NULL;
			list = NULL;
			return (NULL);
		}
	}
	free((*list));
	(*list) = NULL;
	list = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list = ft_lstfd(&head, fd);
	list->nl_position = NULL;
	while (list->nl_position == NULL)
	{
		list->offset = read(list->fd, list->data, BUFFER_SIZE);
		list->data[list->offset] = '\0';
		if (list->offset == -1 || list->offset == 0)
			return (ft_rtn(&list));
		list->tmp_str = ft_strjoin(list->backup, list->data);
		free(list->backup);
		list->backup = NULL;
		list->backup = list->tmp_str;
		list->tmp_str = NULL;
		list->nl_position = ft_strchr(list->backup, '\n');
	}
	list->tmp_chr = list->nl_position[1];
	list->nl_position[1] = '\0';
	line = ft_strdup(list->backup);
	list->nl_position[1] = list->tmp_chr;
	list->tmp_str = ft_strdup(list->nl_position + 1);
	free(list->backup);
	list->backup = NULL;
	list->backup = list->tmp_str;
	list->tmp_str = NULL;
	return (line);
}

// int main()
// {
// 	int fd[2];
// 	char *str;

// 	fd[0] = open("empty.txt", O_RDONLY);
// 	//fd[1] = open("ttt.txt", O_RDONLY);
	
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	//printf("str : %s\n", str);
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	free(str);
// 	//str = get_next_line(fd[1]);
// 	//printf("str2 : %s", str);
// 	//free(str);
// 	printf("_______print________\n");
// 	close(fd[0]);
// 	//close(fd[1]);
// 	//system("leaks a.out");
// 	//while(1);
// 	return (0);
// }
