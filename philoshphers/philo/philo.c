/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:34 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/17 13:34:21 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (u_int64_t)(1000)) + (time.tv_usec / 1000));
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
		// usleep(200);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (0);
}

void	ft_all_free(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->eating);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		i++;
	}
	free(data->table_forks);
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
	ft_all_free(data);
	return (0);
}
