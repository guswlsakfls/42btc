/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/24 16:48:40 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_eat_done(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock);
	// 철학자가 다 먹었는지
	if (data->num_philo_eat_done != data->num_philo)
	{
		pthread_mutex_unlock(&data->lock);
		return (0);
	}
	// if philo eat done all, must put fork down
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
	data->flag_eat_done = FINISH;
	pthread_mutex_unlock(&data->lock);
	return (FINISH);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->flag_death != FINISH && data->flag_eat_done != FINISH)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (ft_philo_die(data, &data->philo[i]) == FINISH)
			{
				pthread_mutex_lock(&data->check_finish);
				// 한번만 체크하면 모두 접근할 수 있다.
				data->flag_death = FINISH;
				pthread_mutex_unlock(&data->check_finish);
				break ;
			}
			else if (ft_philo_eat_done(data, &data->philo[i]) == FINISH)
			{
				pthread_mutex_lock(&data->check_finish);
				// 한번만 체크하면 모두 접근할 수 있다.
				data->flag_eat_done = FINISH;
				pthread_mutex_unlock(&data->check_finish);
				break ;
			}
			i++;
		}
	}
	return ((void **)SUCCESS);
}

int	ft_philo_die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock);
	// 현재 시간
	philo->end_eat_ms = ft_get_time();
	// 죽지 않으면 통과. / 여기서 계속해서 start_eat_ms 는 업데이트 되야 죽지 않는다.
	if ((philo->end_eat_ms - philo->start_eat_ms < data->die_ms) && \
		data->flag_death != FINISH)
	{
		pthread_mutex_unlock(&data->lock);
		return (0);
	}
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
	if (data->flag_death == FINISH)
	{
		pthread_mutex_unlock(&data->lock);
		return (FINISH);
	}
	// 첫번째로 죽으면 위에 걸리지 않고 내려와, died 출력하고 죽고, 죽었다고 표시함.
	ft_messaging(data, philo->tid, "died");
	data->flag_death = FINISH;
	pthread_mutex_unlock(&data->lock);
	return (FINISH);
}

void	ft_messaging(t_data *data, int tid, char *message)
{
	pthread_mutex_lock(&data->print);
	if (!(data->flag_death))
	{
		printf("%ld ", ft_get_time() - data->start_philo_ms);
		printf("%d ", tid);
		printf("%s\n", message);
	}
	pthread_mutex_unlock(&data->print);
}

void	ft_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	// pthread_mutex_lock(&data->lock);
	ft_usleep(data->sleep_ms, data);
	ft_messaging(data, philo->tid, "is sleeping");
	// pthread_mutex_unlock(&data->lock);
}

void	*ft_philo_routine(void *routine_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)routine_arg;
	data = philo->data;
	if (philo->tid % 2)
		usleep(200); // 여기 값을 다르게 주면 안 되나?
	while (data->flag_death != FINISH && data->flag_eat_done != FINISH)
	{
		ft_eat(philo);
		if (data->flag_eat_done != FINISH)
			break;
		ft_sleep(philo);
		ft_messaging(data, philo->tid, "is thinking");
	}
	return ((void **)SUCCESS);
}
