#include "philo.h"

int		print(t_philo *philo, int to_write, unsigned long long time_ms)
{
	if (pthread_mutex_lock(&philo->args->write))
		return (1);
	if (to_write == DIE)
	{
		printf("%llu %d died\n", time_ms, philo->philo_id + 1);
		return (1);
	}
	else if (to_write == EAT)
		printf("%llu %d is eating\n", time_ms, philo->philo_id + 1);
	else if (to_write == SLEEP)
		printf("%llu %d is sleeping\n", time_ms, philo->philo_id + 1);
	else if (to_write == FORK)
		printf("%llu %d has taken a fork\n", time_ms, philo->philo_id + 1);
	else if (to_write == THINK)
		printf("%llu %d is thinking\n", time_ms, philo->philo_id + 1);
	if (pthread_mutex_unlock(&philo->args->write))
		return (1);
	return (0);
}