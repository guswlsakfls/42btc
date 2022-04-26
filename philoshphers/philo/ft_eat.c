/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:25:50 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/26 21:17:56 by hyujo            ###   ########.fr       */
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
	// 다른곳에 쉬는 타이밍을 줘야 하기 때문에 끝나면 sleep하지 않고 종료하기 위해 조건을 주었다.
	while (data->flag_death == 0 && data->flag_eat_done == 0)
	{
		if (ft_time_gap(now_time, ft_get_time()) >= time)
			break ;
		usleep(500);
	}
}

void	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->num_philo == 1)
	{
		ft_messaging(data, philo->tid, "has taken a fork");
		ft_usleep(data->die_ms, data);
	}
	else
	{
		pthread_mutex_lock(&data->mutex_forks[philo->l_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		data->table_forks[philo->l_fork] = 0;
		pthread_mutex_lock(&data->mutex_forks[philo->r_fork]);
		ft_messaging(data, philo->tid, "has taken a fork");
		data->table_forks[philo->r_fork] = 0;
		// pthread_mutex_lock(&data->print);
		// check for start eat time
		philo->start_eat_ms = ft_get_time();
		(philo->num_eat)++; // 필로가 먹은 횟수
		if (philo->num_eat == data->num_eat_done)
		{
			pthread_mutex_unlock(&data->lock);
			(data->num_philo_eat_done)++; // 다먹으면 필로숫자 업
			pthread_mutex_unlock(&data->lock);
		}
		ft_messaging(data, philo->tid, "is eating");
		ft_usleep(data->eat_ms, data);
		// pthread_mutex_unlock(&data->print);
		data->table_forks[philo->l_fork] = 1;
		pthread_mutex_unlock(&data->mutex_forks[philo->l_fork]);
		data->table_forks[philo->r_fork] = 1;
		pthread_mutex_unlock(&data->mutex_forks[philo->r_fork]);
	}
}
