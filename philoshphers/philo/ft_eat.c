/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:25:50 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/17 18:29:24 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time_gap(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	now_time;

	now_time = ft_get_time();
	while (data->death == 0)
	{
		if (ft_time_gap(now_time, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}

// when philo eating, if dead, must do die.
// int	is_enough(t_data *data, t_philo *philo, long long required_ms)
// {
// 	long long	require_ms;
// 	long long	time_ms;

// 	philo->end_ms = ft_get_time();
// 	require_ms = philo->end_ms - philo->start_ms + required_ms;
// 	if (require_ms > arg->die_ms)
// 	{
// 		time_ms = arg->die_ms - (philo->end_ms - philo->start_ms);
// 		ft_usleep_ms(time_ms);
// 		is_die(base, arg, philo);
// 		return (IS_FINISH);
// 	}
// 	return (0);
// }

void	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->num_philo == 1)
		return ; // when philo one, do eat
	else
	{
		ft_philo_die(data, philo);
		pthread_mutex_lock(&data->mutex_forks[philo->l_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		data->table_forks[philo->l_fork] = 0;
		pthread_mutex_lock(&data->mutex_forks[philo->r_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		data->table_forks[philo->r_fork] = 0;
		ft_messaging(data, philo->tid, "is eating");
		// check for start eat time
		philo->start_eat_ms = ft_get_time();
		if (philo->num_eat > 0)
			(philo->num_eat)--;
		ft_usleep(data->eat_ms, data);
		ft_philo_die(data, philo);
		data->table_forks[philo->l_fork] = 1;
		data->table_forks[philo->r_fork] = 1;
		pthread_mutex_unlock(&data->mutex_forks[philo->l_fork]);
		pthread_mutex_unlock(&data->mutex_forks[philo->r_fork]);
		ft_philo_die(data, philo);
	}
}
