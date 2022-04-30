/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:52:45 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/30 18:24:36 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_issapce(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

long long	ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long long	res;

	i = 0;
	while (ft_issapce(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	res = 0;
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (SUCCESS);
	return (ERROR);
}

int	ft_error(int error)
{
	if (error == 1)
		printf("Error\nWrong amount of args.\n");
	if (error == 2)
		printf("Error\nfatal.\n");
	if (error == 3)
		printf("Error\npthread_mutex_init.\n");
	else if (error == 4)
		printf("Error\nInvalid Arguments.\n");
	return (ERROR);
}

void	ft_free(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		i++;
	}
	free(data->mutex_forks);
	free(data->philo);
	free(data);
}
