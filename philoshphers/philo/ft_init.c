/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:31:10 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/24 16:05:19 by hyujo            ###   ########.fr       */
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
	else if (error == 4)
		printf("Error\nInvalid Arguments\n");
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

int	*ft_init_table_forks(t_data *data)
{
	int	*table_forks;
	int	i;

	table_forks = malloc(sizeof(int) * data->num_philo);
	if (table_forks == NULL)
		return (NULL);
	i = 0;
	while (i < data->num_philo)
	{
		table_forks[i] = 1;
		i++;
	}
	return (table_forks);
}

int	ft_data_init(int argc, char **argv, t_data *data)
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
	data->num_philo_eat_done = 0;
	data->start_philo_ms = 0;
	data->flag_death = 0;
	data->mutex_forks = ft_init_mutex_forks(data);
	data->table_forks = ft_init_table_forks(data);
	pthread_mutex_init(&(data->print), NULL);
	pthread_mutex_init(&(data->lock), NULL);
	pthread_mutex_init(&(data->check_finish), NULL);
	data->monitor = malloc(sizeof(pthread_t));
	if (data->monitor == NULL)
		return (ERROR);
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
		data->philo[i].thread = malloc(sizeof(pthread_t));
		if (data->philo[i].thread == NULL)
			return (ERROR);
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->num_philo;
		// start_eat_ms 가 계속 0이면 죽어서 현재 시간으로 초기화 시켜준다.
		data->philo[i].start_eat_ms = ft_get_time();
		data->philo[i].sleeping_ms = 0;
		data->philo[i].end_eat_ms = 0;
		data->philo[i].num_eat = 0;
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
