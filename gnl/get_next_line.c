/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:16:16 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/11 19:30:24 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char 			*data;
	static t_list	*head;
	int				offset;
	int				len;
	char			*line;

	if (head == NULL)
		head = malloc(sizeof(t_list));
	if (head->backup == NULL)
		head->backup = ft_strdup("");
	data = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (data == NULL)
		return (NULL);
	offset = 1;
	while (offset != 0 && !ft_strchr(head->backup, '\n'))
	{
		offset = read(fd, data, BUFFER_SIZE);
		if (offset == -1)
		{
			free(data);
			return (NULL);
		}
		data[offset] = '\0';
		head->backup = ft_strjoin(head->backup, data);
		printf("%c", head->backup[10000000]);
	}
	len = ft_strchr(head->backup, '\n') - head->backup;
	line = ft_substr(head->backup, 0, len + 1);
	head->backup = ft_strchr(head->backup, '\n') + 1;
	free(data);
	return (line);
}

int main()
{
	int fd;
	char *str;

	fd = open("ttt.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str[0] == '\0')
			break ;
		//printf("%d", str[0]);
	}
	//printf("%d", str[10]);
	close(fd);
	return (0);
}
