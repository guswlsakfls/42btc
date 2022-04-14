/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:31:10 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/14 19:14:49 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int error)
{
	if (error == 1)
		printf("Wrong amount of args.\n");
	else if (error == 2)
		printf("Error while parsing.\n");
	else if (error == 3)
		printf("Error while creating threads.\n");
	return (ERROR);
}

t_data	*ft_init(int argc, char **argv)
{
	t_data	*data;

	if ((ft_check_arg(argc, argv)) == ERROR)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (ft_data_init(argc, argv, data) == ERROR || ft_philo_init(data) == ERROR)
		return (0);
	return (data);
}

int	ft_data_init(int argc, char **argv, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	data->die_ms = ft_atoi(argv[2]);
	data->eat_ms = ft_atoi(argv[3]);
	data->sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->num_eat = ft_atoi(argv[5]);
		data->eat_done = 0;
	}
	else
		data->num_eat = 0;
	if (!data->num_philo || !data->die_ms
		|| !data->eat_ms || !data->sleep_ms)
	{
		printf("Error\nInvalid Arguments\n");
		return (ERROR);
	}
	data->start_ms = 0;
	data->dead = 0;
	data->forks = ft_init_fork(data);
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&(data->eating), NULL);
	return (SUCCESS);
}

pthread_mutex_t	*ft_init_fork(t_data *data)
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

	data->philo = (t_philo *)malloc(sizeof(t_philo) * (data->num_philo));
	if (data->philo == NULL)
		return (ERROR);
	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].thread = malloc(sizeof(pthread_t));
		if (data->philo[i].thread == NULL)
			return (ERROR);
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->num_philo;
		data->philo[i].eating_ms = 0;
		data->philo[i].sleeping_ms = 0;
		data->philo[i].end_ms = 0;
		data->philo[i].num_eat = 0;
		data->philo[i].flag_eat = 0;
		data->philo[i].data = data;
		data->philo[i].tid = i + 1;
		i++;
	}
	return (SUCCESS);
}

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
