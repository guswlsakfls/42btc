/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:29:51 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 14:38:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int index;

	index = 0;
	while (str[index] == '\0')
	{
		if ('A' <= str[index] && str[index] <= 'Z')
		{
			str[index] = str[index] + 32;
		}
		index++;
	}
	return (str);
}
