/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:37:32 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:37:32 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

static void	sfree(char *s)
{
	if (!s)
		return ;
	if (s)
		free(s);
}

static char	*snull(char *s, char **line)
{
	if (!s)
		*line = ft_strdup("\0");
	return (s);
}

static char	*rline(char **line, char *s)
{
	size_t	i;
	char	*temp;

	if (!s)
	{
		s = snull(s, line);
		return (s);
	}
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		*line = ft_strdup(s);
		sfree(s);
		s = NULL;
	}
	else if (s[i] == '\n')
	{
		*line = ft_strnldup(s);
		temp = ft_strdup(&s[++i]);
		sfree(s);
		s = temp;
	}
	return (s);
}

int			get_next_line(int fd, char **line)
{
	int				rev;
	char			*buff;
	char			*temp;
	static char		*s;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	while (0 < (rev = read(fd, buff, BUFFER_SIZE)))
	{
		buff[rev] = '\0';
		if (s == NULL)
			s = ft_strdup("\0");
		temp = ft_strjoin(s, buff);
		sfree(s);
		s = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	sfree(buff);
	s = rline(line, s);
	if (rev == 0 && s == NULL)
		return (0);
	return (rev < 0 ? -1 : 1);
}
