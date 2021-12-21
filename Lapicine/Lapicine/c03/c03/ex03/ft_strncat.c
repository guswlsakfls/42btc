/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:08:35 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/15 21:11:32 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[j] != 0)
		j++;
	while (i < nb && src[i] != 0)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = 0;
	return (dest);
}
