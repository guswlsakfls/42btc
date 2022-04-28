/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:34 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/28 15:01:58 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_pthread(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philo;
	data->start_philo_ms = ft_get_time();
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, \
						&ft_philo_routine, &(data->philo[i])) != 0)
			return (ERROR);
		usleep(1);
		i++;
	}
	ft_monitor(data);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_init(argc, argv);
	if (data == NULL)
		return (ERROR);
	if (ft_philo_pthread(data) == ERROR)
		return (ft_error(2));
	ft_free(data);
	return (0);
}
