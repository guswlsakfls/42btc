/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoshopers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:34 by hyujo             #+#    #+#             */
/*   Updated: 2022/04/05 19:07:06 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex_lock;

int	g_count;

void	*t_func(void *data)
{
	int			i;
	char		*thread_name;

	thread_name = (char *)data;
	pthread_mutex_lock(&mutex_lock);
	g_count = 0;
	i = -1;
	while (++i < 3)
	{
		printf("%s COUNT %d\n%d\n", thread_name, g_count, i);
		g_count++;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex_lock);
}

int	main(void)
{
	pthread_t p_thread1;
	pthread_t p_thread2;

	pthread_mutex_init(&mutex_lock, NULL);
	pthread_create(&p_thread1, NULL, t_func, (void *)"Thread1");
	pthread_create(&p_thread2, NULL, t_func, (void *)"Thread2");
	pthread_join(p_thread1, NULL);
	pthread_join(p_thread2, NULL);
	return (0);
}
