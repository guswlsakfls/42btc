/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:16:16 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/15 21:30:15 by hyujo            ###   ########.fr       */
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

char	*ft_rtn(t_list **list, int offset)
{
	char	*line;

	if (offset == 0)
	{
		if ((*list)->backup != NULL)
		{
			line = ft_strdup((*list)->backup);
			free((*list)->backup);
			(*list)->backup = NULL;
			free(*list);
			*list = NULL;
			return (line);
		}
		else
		{
			*list = NULL;
			return (NULL);
		}
	}
	else
	{
		free(*list);
		*list = NULL;
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*list;
	char			*line;
	char			data[BUFFER_SIZE + 1];
	int				offset;
	char			*tmp_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list = ft_lstfd(&head, fd);
	offset = 0;
	while (!ft_strchr(list->backup, '\n'))
	{
		offset = read(list->fd, data, BUFFER_SIZE);
		if (offset <= 0)
			return (ft_rtn(&list, offset));
		data[offset] = '\0';
		tmp_str = ft_strjoin(list->backup, data);
		free(list->backup);
		list->backup = tmp_str;
		tmp_str = NULL;
	}
	offset = 0;
	while (list->backup[offset] != '\n')
		offset++;
	line = malloc(sizeof(char) * (offset + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, list->backup, offset + 2); // 왜 + 2 인가, \n 에서 끝나니까
	tmp_str = ft_strdup(&list->backup[offset + 1]);
	free(list->backup);
	list->backup = tmp_str;
	tmp_str = NULL;
	return (line);
}

// int main()
// {
// 	int fd[2];
// 	char *str;

// 	fd[0] = open("./gnlTester/files/42_with_nl", O_RDONLY);
// 	//fd[1] = open("ttt.txt", O_RDONLY);
	
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	//printf("str : %s\n", str);
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
// 	str = get_next_line(fd[0]);
// 	printf("str1 : %s", str);
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
