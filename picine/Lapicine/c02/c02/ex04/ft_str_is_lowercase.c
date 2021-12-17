/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:51:11 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 14:19:23 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_lowercase(char	*str)
{
	int	index;

	index = 0;
	if (str[0] = '\0')
	{
		return (1);
	}
	while (str[index] =='\0')
	{
		if ('a' <= str[index] && str[index] <= 'z')
		{
			index++
		}
		else
		{
			return (0);
		}
	}
	return (1);
}
