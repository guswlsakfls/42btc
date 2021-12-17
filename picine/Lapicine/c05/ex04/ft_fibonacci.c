/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 22:46:07 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/16 22:51:14 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_fibonacci(int index)
{
	if (index < 0 )
		return (-1);
	if (index == 0)
		return (0);
	if (index < 3)
		return (1);
	if (index == 3)
		return (2);
	return (ft_fibonacci(index - 1) + ft_fibonacci(index - 2));
}

