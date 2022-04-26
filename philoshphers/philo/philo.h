/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:46:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/26 21:11:00 by hyujo            ###   ########.fr       */
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
# define SUCCESS 1
# define FINISH 1

typedef struct s_data
{
	int				num_philo;
	long int		die_ms;
	long int		eat_ms;
	long int		sleep_ms;
	long int		num_eat_done; // 먹어야 끝나는 철학자 수
	long int		num_philo_eat_done; // 다 먹은 철학자 수
	int				flag_eat_done; // 철학자들이 다 먹으면 종료
	long int		start_philo_ms; // 시작 시간
	int				flag_death;
	int				*table_forks;
	pthread_t		monitor;
	pthread_mutex_t	lock;
	pthread_mutex_t	print; // 프린트 할때 뮤텍스 락
	pthread_mutex_t	*mutex_forks; // 포크 개수만큼 뮤텍스 락
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				r_fork; // 왜 필요한가? -> mutex_fork 에 인덱스 번호로 접근하기 위해.
	int				l_fork;
	long int		start_eat_ms; // 먹는 시간
	long int		sleeping_ms; // 자고있는 시간
	long int		end_eat_ms; // 끝나는 시간
	int				num_eat; // 먹은 횟수
	int				tid;
	t_data			*data;
}	t_philo;

// utils
void			*ft_malloc(size_t size, size_t cnt);
void			ft_bzero(void *s, size_t n);
int				ft_issapce(char c);
long long		ft_atoi(const char *str);
int				ft_isdigit(int c);
void			*ft_philo_routine(void *routine_arg);

// init
t_data			*ft_init(int argc, char **argv);
int				ft_check_arg(int argc, char **argv);
int				ft_data_init(int argc, char **argv, t_data *data);
int				ft_philo_init(t_data *data);
pthread_mutex_t	*ft_init_mutex_forks(t_data *data);

// time
long			ft_get_time(void);

// routine
void			ft_messaging(t_data *data, int tid, char *message);
void			ft_eat(t_philo *philo);
void			ft_usleep(long long time, t_data *data);
int				ft_philo_die(t_data *data, t_philo *philo);
void			*ft_monitor(void *data);

#endif
