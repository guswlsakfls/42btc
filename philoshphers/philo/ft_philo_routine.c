/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/26 21:03:04 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_eat_done(t_data *data)
{
	pthread_mutex_lock(&data->print);
	// 철학자가 다 먹었는지
	if (data->num_philo_eat_done != data->num_philo)
	{
		pthread_mutex_unlock(&data->print);
		return (0);
	}
	data->flag_eat_done = FINISH;
	pthread_mutex_unlock(&data->print);
	return (FINISH);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (ft_philo_die(data, &data->philo[i]) == FINISH)
				return ((void *)SUCCESS);
			else if (ft_philo_eat_done(data) == FINISH)
				return ((void *)SUCCESS);
			i++;
		}
	}
	return ((void *)SUCCESS);
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
		// pthread_mutex_unlock(&data->print);
		return (0);
	}
	if (data->flag_death == FINISH)
	{
		// pthread_mutex_unlock(&data->print);
		return (FINISH);
	}
	// 여기가 무한 동력 걸린다. 슈바 그러면 하나 더 만들어ㅏ야 하나?
	ft_messaging(data, philo->tid, "died");
	data->flag_death = FINISH;
	pthread_mutex_unlock(&data->lock);
	return (FINISH);
}

void	ft_messaging(t_data *data, int tid, char *message)
{
	pthread_mutex_lock(&data->print);
	if (data->flag_death != FINISH && data->flag_eat_done != FINISH)
		printf("%ld %d %s\n", ft_get_time()
			- data->start_philo_ms, tid, message);
	pthread_mutex_unlock(&data->print);
}

void	ft_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_messaging(data, philo->tid, "is sleeping");
	ft_usleep(data->sleep_ms, data);
}

void	*ft_philo_routine(void *routine_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)routine_arg;
	data = philo->data;
	if (philo->tid % 2)
		usleep(200);
	while (data->flag_death != FINISH && data->flag_eat_done != FINISH)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_messaging(data, philo->tid, "is thinking");
		usleep(100);
	}
	return ((void *)SUCCESS);
}
