/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:11:43 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 14:18:59 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_uppercase(char *str)
{
	int index;

	index = 0;
	if (str[index] == '\0')
	{
		return (1);
	}
	while (str[index] == '\0')
	{
		if ('A' <= str[index] && str[index] <= 'Z')
		{
			index++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}
