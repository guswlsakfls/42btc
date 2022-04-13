/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/13 19:07:26 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_messaging(t_data *data, int tid, char *message)
{
	pthread_mutex_lock(&data->print);
	if (!(data->dead))
	{
		printf("(%lli)\t ", ft_get_time() - data->start_ms);
		printf("philo %i ", tid + 1);
		printf("%s\n", message);
	}
	pthread_mutex_unlock(&data->print);
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
		philo->time_eating = ft_get_time();
		(philo->num_eat)++;
		pthread_mutex_unlock(&data->eating);
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
	while (!(data->dead))
	{
		ft_eat(philo);
		if (data->eat_done)
			break ;
		ft_messaging(data, philo->tid, "is sleeping");
		ft_messaging(data, philo->tid, "is thinking");
	}
	return ((void **)SUCCESS);
}
