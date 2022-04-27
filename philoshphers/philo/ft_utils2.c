/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:17:52 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/27 20:26:53 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 6 && argc != 5)
		return (ft_error(1));
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == ERROR)
				return (ft_error(1));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_error(int error)
{
	if (error == 1)
		printf("Wrong amount of args.\n");
	else if (error == 4)
		printf("Error\nInvalid Arguments.\n");
	return (ERROR);
}
