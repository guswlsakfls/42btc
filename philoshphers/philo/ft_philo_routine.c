/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/14 20:27:22 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_messaging(t_data *data, int tid, char *message)
{
	pthread_mutex_lock(&data->print);
	if (!(data->dead))
	{
		printf("(%i)\t", ft_get_time() - data->start_ms);
		printf("philo %i ", tid);
		printf("%s\n", message);
	}
	pthread_mutex_unlock(&data->print);
}

long long	ft_time_gap(long long past, long long pres)
{
	return (pres - past);
}

void	ft_acting(long long time, t_data *data)
{
	long long	t;

	t = ft_get_time();
	while (!(data->dead))
	{
		if (ft_time_gap(t, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}

void	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->num_philo == 1)
		return ; // when philo one, do eat
	else
	{
		pthread_mutex_lock(&data->forks[philo->l_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->r_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		pthread_mutex_lock(&data->eating);
		ft_messaging(data, philo->tid, "is eaing");
		philo->eating_ms = ft_get_time();
		(philo->num_eat)++;
		pthread_mutex_unlock(&data->eating);
		ft_acting(data->eat_ms, data);
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
	}
}

void	*ft_philo_routine(void *routine_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)routine_arg;
	data = philo->data;
	if (philo->tid % 2)
		usleep(20000);
	while (!(data->dead))
	{
		ft_eat(philo);
		if (data->eat_done)
			break ;
		ft_messaging(data, philo->tid, "is sleeping");
		ft_acting(data->sleep_ms, data);
		ft_messaging(data, philo->tid, "is thinking");
	}
	return ((void **)SUCCESS);
}
