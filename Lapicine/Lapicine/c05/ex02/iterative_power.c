/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_power.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 22:34:34 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/16 22:37:50 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int res;

	res = 1;
	if (power < 0)
		return (0);
	while (power > 0)
	{
		res *= nb;
		power--;
	}
	return (res);
}
