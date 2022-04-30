/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:17:52 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/30 18:24:43 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_longlong_digit(char *argv)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == ERROR)
			return (ERROR);
		res = res * 10 + argv[i] - '0';
		if (res < 1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	ft_check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 6 && argc != 5)
		return (ft_error(1));
	i = 1;
	while (argv[i])
	{
		if (ft_longlong_digit(argv[i]) == ERROR)
			return (ft_error(1));
	i++;
	}
	return (SUCCESS);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	ft_time_gap(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	now_time;

	now_time = ft_get_time();
	while (data->flag_death != FINISH && data->flag_eat_done != FINISH)
	{
		if (ft_time_gap(now_time, ft_get_time()) >= time)
			break ;
		usleep(500);
	}
}
