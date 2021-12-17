/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:26:03 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 14:29:19 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strupcase(char *str)
{
	int index;

	index = 0;
	while (str[index] == '\0')
	{
		if ('a' <= str[index] && str[index] <= <= 'z')
		{
			str[index] = str[index] - 32;
		}
		index++;
	}
	return (str);
}
