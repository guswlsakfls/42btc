/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:46:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/17 13:09:58 by hyujo            ###   ########.fr       */
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
	int				die_ms;
	int				eat_ms;
	int				sleep_ms;
	int				num_eat;
	int				eat_done; // 할당량을 채운 철학자의 수 저장
	int				start_philo_ms; // 시작 시간
	int				finish;
	int				*table_forks;
	pthread_mutex_t	print; // 프린트 할때 뮤텍스 락
	pthread_mutex_t	*mutex_forks; // 포크 개수만큼 뮤텍스 락
	pthread_mutex_t	eating;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				r_fork; // 왜 필요한가? -> mutex_fork 에 인덱스 번호로 접근하기 위해.
	int				l_fork;
	int				start_eat_ms; // 먹는 시간
	int				sleeping_ms; // 자고있는 시간
	int				end_eat_ms; // 끝나는 시간
	int				num_eat; // 먹은 횟수
	int				flag_eat; // 먹은 횟수 종료 플래그
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
int				ft_get_time(void);

// routine
void			ft_messaging(t_data *data, int tid, char *message);
void			ft_eat(t_philo *philo);
void			ft_usleep(long long time, t_data *data);

#endif
