/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/15 19:42:23 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_die(t_data *data, t_philo *philo)
{
	philo->end_ms = ft_get_time();
	if ((philo->end_ms - philo->start_eat_ms < data->die_ms) && \
		data->finish != FINISH)
		return (0);
	if (data->table_forks[philo->l_fork] == 0)
	{
		data->table_forks[philo->l_fork] = 1;
		pthread_mutex_unlock(&(data->mutex_forks[philo->l_fork]));
	}
	if (data->table_forks[philo->r_fork] == 0)
	{
		data->table_forks[philo->r_fork] = 1;
		pthread_mutex_unlock(&(data->mutex_forks[philo->r_fork]));
	}
	if (data->finish == FINISH)
		return (FINISH);
	// 죽어야 한다.
	ft_messaging(data, philo->tid, "died");
	data->finish = FINISH;
	return (FINISH);
}

void	ft_messaging(t_data *data, int tid, char *message)
{
	pthread_mutex_lock(&data->print);
	if (!(data->finish))
	{
		printf("%i ", ft_get_time() - data->start_philo_ms);
		printf("%i ", tid);
		printf("%s\n", message);
	}
	pthread_mutex_unlock(&data->print);
}

void	*ft_philo_routine(void *routine_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)routine_arg;
	data = philo->data;
	if (philo->tid % 2)
		usleep(200);
	while (!(data->finish))
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
