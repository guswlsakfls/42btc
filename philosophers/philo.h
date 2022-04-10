/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:46:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/10 19:53:09 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

# define ERROR 0
# define SUCCESS 0

typedef struct s_arg
{
	int	num_philo;
	int	die_ms;
	int	eat_ms;
	int	sleep_ms;
	int	num_eat;
	int	eat_done;
}	t_arg;

typedef struct s_philo
{
	pthread_t	*tid;
	int			r_fork;
	int			l_fork;
	int			num_sleeping;
	int			start_ms;
	int			end_ms;
	int			num_eat;
	int			flag_eat;
	int			num;
}	t_philo;

typedef struct s_data
{
	t_arg			*arg;
	t_philo			*philo;
	int				*philo_fork;
	int				th_index;
	int				routine_arg;
	struct s_mutex	*mutex;
	struct timeval	start_tv;
	struct timeval	life_tv;
}	t_data;

// ft_utils.c
void		*ft_malloc(size_t size, size_t cnt);
void		ft_bzero(void *s, size_t n);
static int	ft_issapce(char c);
long long	ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*ft_philo_routine(void *routine_arg);

#endif
