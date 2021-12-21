/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:12:28 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 19:34:13 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned	int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int index;

	index = 0;
	while (index < size - 1)
	{
		if (src[index] == '\0')
		{
			break ;
		}
		else
		{
			dest[index] = src[index];
			index++;
		}
	}
	dest[index] = '\0';
	while (src[index] != '\0')
	{
		index++;
	}
	return (index);
}
