#include "philo.h"

unsigned long long	time_passed(unsigned long long start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (((end.tv_sec * 1000) + (end.tv_usec / 1000)) - start);
}

unsigned long long time_now(void)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void sleepu(unsigned long long end)
{
    while (time_now() < end)
        usleep(10);
}