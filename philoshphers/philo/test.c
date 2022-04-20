#include <stdio.h>
#include <sys/time.h>

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("tvsec : %ld\n", time.tv_sec);
	printf("tvusec : %d\n", time.tv_usec);
	printf("tvsec : %ld\n", time.tv_sec * 1000);
	printf("tvusec : %d\n", time.tv_usec / 1000);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main()
{
	long	time;

	time = ft_get_time();
	printf("time : %ld\n", time);
	return (0);
}
