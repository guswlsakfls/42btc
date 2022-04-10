/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:34 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/08 11:29:07 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc > 6 || argc < 5)
		return (ERROR);
	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == ERROR)
				return (ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_arg_init(int argc, char **argv, t_data *data)
{
	data->arg = malloc(sizeof(t_arg));
	if (data->arg == NULL)
		return (ERROR);
	if ((ft_check_arg(argc, argv)) == ERROR)
		return (ERROR);
	data->arg->num_philo = ft_atoi(argv[1]);
	if (data->arg->num_philo == 0)
		return (ERROR);
	data->arg->num_fork = data->arg->num_philo;
	data->arg->die_ms = ft_atoi(argv[2]);
	data->arg->eat_ms = ft_atoi(argv[3]);
	data->arg->sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->arg->num_eat = ft_atoi(argv[5]);
		data->arg->eat_done = 0;
	}
	else
		data->arg->num_eat = 0;
	return (SUCCESS);
}

int	ft_philo_init(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * (data->arg->num_philo));
	if (data->philo == NULL)
		return (ERROR);
	i = 0;
	while (i < data->arg->num_philo)
	{
		data->philo[i].tid = (pthread_t *)malloc(sizeof(pthread_t));
		if (data->philo[i].tid == NULL)
			return (ERROR);
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->arg->num_fork;
		data->philo[i].num_sleeping = 0;
		data->philo[i].start_ms = 0;
		data->philo[i].end_ms = 0;
		data->philo[i].num_eat = 0;
		data->philo[i].flag_eat = 0;
		i++;
	}
	return (SUCCESS);
}

int	ft_fork_mutex_init(t_data *data)
{
	int	i;

	data->mutex = malloc(sizeof(pthread_mutex_t)
			* (data->arg->num_fork));
	if (data->mutex == NULL)
		return (ERROR);
	data->philo_fork = (int *)malloc(sizeof(int) * data->arg->num_fork);
	if (data->philo_fork == NULL)
		return (ERROR);
	i = 0;
	while (i < data->arg->num_fork)
	{
		pthread_mutex_init(&(data->mutex[i]), NULL); // mutex 변수는 배열이 아닌가?
		data->philo_fork[i] = 1;
		i++;
	}
	// pthread_mutex_init(&(data->ft_mutex), NULL);
	return (SUCCESS);
}

int	ft_philo_pthread(t_data *data, t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < arg->num_philo)
	{
		data->th_index = i;
		pthread_create(philo[data->th_index].tid, NULL, \
						ft_philo_routine, data);
		usleep(200);
		i++;
	}
	i = 0;
	while (i < arg->num_philo)
	{
		// 메인 쓰레드의 대기 영역 //
		pthread_join(*(philo[i].tid), NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(data));
	if (data == NULL)
		return (0);
	if (ft_arg_init(argc, argv, data) == ERROR)
		return (0);
	if (ft_philo_init(data) == ERROR)
		return (0);
	return (0);
}
