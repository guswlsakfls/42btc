/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:25:50 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/27 22:14:34 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_check_eat_done(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&data->print);
	(philo->num_eat)++;
	if (philo->num_eat == data->num_eat_done)
	{
		(data->num_philo_eat_done)++;
		if (data->num_philo_eat_done == data->num_philo)
		{
			data->flag_eat_done = FINISH;
			printf("%ld [%d] %s\n", ft_get_time()
				- data->start_philo_ms, philo->tid, "is eating");
			usleep(1000);
		}
	}
	pthread_mutex_unlock(&data->print);
}

void	ft_eat(t_data *data, t_philo *philo)
{
	if (data->num_philo == 1)
	{
		ft_messaging(data, philo->tid, "has taken a fork");
		ft_usleep(data->die_ms, data);
	}
	else
	{
		pthread_mutex_lock(&data->mutex_forks[philo->l_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		pthread_mutex_lock(&data->mutex_forks[philo->r_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		philo->start_eat_ms = ft_get_time();
		ft_check_eat_done(data, philo);
		ft_messaging(data, philo->tid, "is eating");
		ft_usleep(data->eat_ms, data);
		pthread_mutex_unlock(&data->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&data->mutex_forks[philo->r_fork]);
	}
}
