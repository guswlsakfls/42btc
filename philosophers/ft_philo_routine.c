/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:25:42 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/08 11:28:41 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_routine(void *routine_arg)
{
	t_data	*data;
	t_arg	*arg;
	t_philo	*philo;

	data = (t_data *)routine_arg;
	arg = data->arg;
	philo = &(data->philo[data->th_index]);
	philo->num = data->th_index;
	pthread_mutex_lock(&(data->ft_mutex));
	data->timestamp_start_ms = get_time_ms();
	pthread_mutex_unlock(&(base->ft_mutex));
	wait_create_thread(base, arg, philo);
	if (philo->num % 2 == 1)
		usleep(200 * (arg->num_philo - philo->num + 1));
	if ((act_except(base, arg, philo)) == IS_FINISH)
		return ((void **)IS_FINISH);
	while (base->is_finish != IS_FINISH)
	{
		if ((philo_act(base, arg, philo)) == IS_FINISH)
			break ;
	}
	return ((void **)IS_FINISH);
}
