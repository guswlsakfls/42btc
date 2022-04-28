/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/28 14:19:42 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_monitor(t_data *data)
{
	int		i;

	while (data->flag_death != FINISH && data->flag_eat_done != FINISH)
	{
		i = 0;
		while (i < data->num_philo && data->flag_eat_done != FINISH)
		{
			if (ft_philo_die(data, &data->philo[i]) == FINISH)
				break ;
			i++;
		}
	}
}

int	ft_philo_die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print);
	philo->end_eat_ms = ft_get_time();
	if (((philo->end_eat_ms - philo->start_eat_ms < data->die_ms) && \
		data->flag_death != FINISH) || data->flag_eat_done == FINISH)
	{
		pthread_mutex_unlock(&data->print);
		return (0);
	}
	data->flag_death = FINISH;
	usleep(1000);
	printf("%lld [%d] %s\n", ft_get_time()
		- data->start_philo_ms, philo->tid, "is died");
	pthread_mutex_unlock(&data->print);
	return (FINISH);
}

void	ft_messaging(t_data *data, int tid, char *message)
{
	pthread_mutex_lock(&data->print);
	if (data->flag_death != FINISH && data->flag_eat_done != FINISH)
		printf("%lld [%d] %s\n", ft_get_time()
			- data->start_philo_ms, tid, message);
	pthread_mutex_unlock(&data->print);
}

void	ft_sleep(t_data *data, t_philo *philo)
{
	ft_messaging(data, philo->tid, "is sleeping");
	ft_usleep(data->sleep_ms, data);
}

void	*ft_philo_routine(void *routine_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)routine_arg;
	philo->start_eat_ms = ft_get_time();
	data = philo->data;
	if (philo->tid % 2)
		usleep(200);
	while (data->flag_death != FINISH && data->flag_eat_done != FINISH)
	{
		ft_eat(data, philo);
		ft_sleep(data, philo);
		ft_messaging(data, philo->tid, "is thinking");
		usleep(1);
	}
	return ((void *)SUCCESS);
}
