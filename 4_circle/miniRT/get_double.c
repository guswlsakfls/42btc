/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:37:16 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:37:16 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

int	ft_str_isdouble(char *str)
{
	int		i;
	int		dot;

	i = 0;
	dot = 0;
	if (i == 0 && (str[i] == '-' || str[i] == '+'))
		i++;
	while (i < (int)ft_strlen(str))
	{
		if (!(ft_isdigit(str[i]) == 1 || str[i] == '.'))
			return (0);
		if (str[i] == '.')
			dot++;
		if (str[i] == '.' && dot > 1)
			exit(1);
		i++;
	}
	return (1);
}

double	get_double(char *str)
{
	if (ft_str_isdouble(str) == 0)
		exit(1);
	return (ft_atof(str));
}

double	get_ratio(char *str)
{
	double	nbr;

	nbr = get_double(str);
	if (!(nbr >= 0.0 && nbr <= 1.0))
		exit(1);
	return (nbr);
}

double	get_size(char *str)
{
	double	nbr;

	nbr = get_double(str);
	if (!(nbr > 0.0))
		exit(1);
	return (nbr);
}
