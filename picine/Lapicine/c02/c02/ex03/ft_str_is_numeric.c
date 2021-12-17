/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:45:57 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 14:19:50 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_numeric(char *str)
{
	int	index;

	index = 0;
	if (str[0] == '\0')
	{
		return (1);
	}
	while (str[index] == '\0')
	{
		if ('0' <= str[index] && str[index] <= '9')
		{
			return (1);
		}
		else
		{
			return (0);
		}
	return (1);
	}
}
