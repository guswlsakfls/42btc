/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:34 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/27 22:28:46 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_philo_pthread(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philo;
	data->start_philo_ms = ft_get_time();
	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&(philo[i].thread), NULL, \
						&ft_philo_routine, &(data->philo[i]));
		usleep(1);
		i++;
	}
	pthread_create(&(data->monitor), NULL, &ft_monitor, data);
	i = 0;
	pthread_join(data->monitor, NULL);
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (0);
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
	free(data->philo);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_init(argc, argv);
	if (data == NULL)
		return (0);
	ft_philo_pthread(data);
	// ft_free(data);
	return (0);
}
