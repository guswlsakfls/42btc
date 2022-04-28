/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:31:10 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/28 13:02:25 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ft_init(int argc, char **argv)
{
	t_data	*data;

	if ((ft_check_arg(argc, argv)) == ERROR)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (ft_data_init(argc, argv, data) == ERROR || ft_philo_init(data) == ERROR)
		return (NULL);
	return (data);
}

int	ft_arg_init(int argc, char **argv, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	data->die_ms = ft_atoi(argv[2]);
	data->eat_ms = ft_atoi(argv[3]);
	data->sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->num_eat_done = ft_atoi(argv[5]);
		if (data->num_eat_done < 1)
			return (ft_error(4));
	}
	else
		data->num_eat_done = -1;
	if (data->num_philo < 1 || data->die_ms < 1
		|| data->eat_ms < 1 || data->sleep_ms < 1)
		return (ft_error(4));
	return (SUCCESS);
}

int	ft_data_init(int argc, char **argv, t_data *data)
{
	if (ft_arg_init(argc, argv, data) == ERROR)
		return (ERROR);
	data->num_philo_eat_done = 0;
	data->start_philo_ms = 0;
	data->flag_eat_done = 0;
	data->flag_death = 0;
	data->mutex_forks = ft_init_mutex_forks(data);
	pthread_mutex_init(&(data->print), NULL);
	return (SUCCESS);
}

pthread_mutex_t	*ft_init_mutex_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!forks)
		return (NULL);
	while (++i < data->num_philo)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

int	ft_philo_init(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * (data->num_philo));
	if (data->philo == NULL)
		return (ERROR);
	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].l_fork = (i + 1) % data->num_philo;
		data->philo[i].r_fork = i;
		data->philo[i].start_eat_ms = 0;
		data->philo[i].end_eat_ms = 0;
		data->philo[i].num_eat = 0;
		data->philo[i].data = data;
		data->philo[i].tid = i + 1;
		i++;
	}
	return (SUCCESS);
}
