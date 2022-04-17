/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/17 13:10:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_die(t_data *data, t_philo *philo)
{
	// 현재 시간
	philo->end_eat_ms = ft_get_time();
	// 죽지 않으면 통과.
	if ((philo->end_eat_ms - philo->start_eat_ms < data->die_ms) && \
		data->finish != FINISH)
		return (0);
	// 죽으면 포크 내려놓고 죽음
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
	// data 전체 구조체에서 미리 죽은 사람이 있으면 출력하지 않고 죽음
	if (data->finish == FINISH)
		return (FINISH);
	// 첫번째로 죽으면 위에 걸리지 않고 내려와, died 출력하고 죽고, 죽었다고 표시함.
	ft_messaging(data, philo->tid, "died");
	data->finish = FINISH;
	return (FINISH);
}

void	ft_messaging(t_data *data, int tid, char *message)
{
	pthread_mutex_lock(&data->print);
	if (!(data->finish))
	{
		printf("%d ", ft_get_time() - data->start_philo_ms);
		printf("%d ", tid);
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
