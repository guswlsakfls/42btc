/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:17:52 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/28 14:14:45 by hyujo            ###   ########.fr       */
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

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	ft_time_gap(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	now_time;

	now_time = ft_get_time();
	while (data->flag_death != FINISH && data->flag_eat_done != FINISH)
	{
		if (ft_time_gap(now_time, ft_get_time()) >= time)
			break ;
		usleep(500);
	}
}
