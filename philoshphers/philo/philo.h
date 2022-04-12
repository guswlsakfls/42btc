/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:46:06 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/12 20:38:30 by hyujo            ###   ########.fr       */
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

typedef struct s_data
{
	int				num_philo;
	int				die_ms;
	int				eat_ms;
	int				sleep_ms;
	int				num_eat;
	int				eat_done;
	int				dead;
	pthread_mutex_t	print; // 프린트 할때 뮤텍스 락
	pthread_mutex_t	*forks; // 포크 개수만큼 뮤텍스 락
	int				start_ms; // 시작 시간
	t_philo			*philo;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	eating;
	int				r_fork; // 왜 필요한가? -> mutex_fork 에 인덱스 번호로 접근하기 위해.
	int				l_fork;
	int				num_sleeping; // 자고있는 시간
	int				end_ms; // 끝나는 시간
	int				num_eat; // 먹은 횟수
	int				flag_eat; // 먹은 횟수 종료 플래그
	int				num;
	t_data			*data;
}	t_philo;

// ft_utils.c
void		*ft_malloc(size_t size, size_t cnt);
void		ft_bzero(void *s, size_t n);
static int	ft_issapce(char c);
long long	ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*ft_philo_routine(void *routine_arg);

// ft_init.c
t_data		*ft_init(int argc, char **argv);

#endif
