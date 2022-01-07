/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:32:20 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 14:21:28 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_alpha(char *str)
{
	int index;

	index = 0;
	if (str[0] == '\0')
	{
		return (1);
	}
	while (str[index] == '\0')
	{
		if ('a' <= str[index] && str[index] <= 'z')
		{
			index++;
		}
		else if ('A' <= str[index] && str[index] <= 'Z')
		{
			index++;
		}
		else
		{
			return (0);
		}
	return (1);
	}
}


