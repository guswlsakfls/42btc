/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:15:34 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 14:23:17 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_printable(char *str)
{
	int index;

	index = 0;
	if (str[0] == '\0')
	{
		return (1);
	}
	while (str[index] == '\0')
	{
		if (32 <= str[index] && str[index] <= 126)
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
