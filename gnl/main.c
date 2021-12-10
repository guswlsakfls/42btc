/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:16:16 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/10 21:53:33 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static t_list	head;
	static char		backup[BUFFER_SIZE];
	int				offset;
	int				len;

	head.data = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (head.data == NULL)
		return (0);
	len = 0;
	while (1)
	{
		len = read(fd, head.data, BUFFER_SIZE);
		if (len > 0 )
			break ;
		ft_strjoin(backup, head.data);
		offset = len;
		if (offset < 0)
		{
			free(head.data);
			return (0);
		}
	}
	head.data[offset] = '\0';
	printf("%s\n", head.data);
	return (0);
}

int main()
{
	int fd;
	char *s;

	fd = open("text.txt", O_RDONLY);
	get_next_line(fd);
	close(fd);
	return (0);
}
