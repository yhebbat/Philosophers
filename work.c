#include "philo.h"

void	eat_helper(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->is_eating);
	philo->last_time_eat = time_now();
	pthread_mutex_unlock(&philo->args->is_eating);
	philo->eat = 1;
	print(philo, EAT, time_passed(philo->start));
	usleep((philo->args->time_eat * 1000) - 10000);
	sleepu(philo->last_time_eat + philo->args->time_eat);
	pthread_mutex_lock(&philo->args->is_eating);
	philo->last_time_eat = time_now();
	philo->eat = 0;
	if (philo->nb_of_meals > 0)
		philo->nb_of_meals--;
	pthread_mutex_unlock(&philo->args->is_eating);
}

void	eat(t_philo *philo)
{
	int right;
	int left;

	if (philo->philo_id % 2 == 0)
		right = (philo->philo_id + 1) % (philo->args->number_philo);
	else
		right = philo->philo_id;
	if (philo->philo_id % 2 == 0)
		left = philo->philo_id;
	else
		left = (philo->philo_id + 1) % (philo->args->number_philo);
	pthread_mutex_lock(&philo->args->forks[left]);
	print(philo, FORK, time_passed(philo->start));
	pthread_mutex_lock(&philo->args->forks[right]);
	print(philo, FORK, time_passed(philo->start));
	eat_helper(philo);
	pthread_mutex_unlock(&philo->args->forks[left]);
	pthread_mutex_unlock(&philo->args->forks[right]);
}

void	ft_sleep(t_philo *philo)
{
	unsigned long long before_sleep;

	before_sleep = time_now();
	print(philo, SLEEP, time_passed(philo->start));
	usleep((philo->args->time_sleep * 1000) - 10000);
	sleepu(philo->args->time_sleep + before_sleep);
}

void	think(t_philo *philo)
{
	print(philo, THINK, time_passed(philo->start));
}

void	*work(void	*philostruct)
{
	t_philo		*philo;

	philo = (t_philo *)philostruct;
	if (philo == NULL || philo->args->num_meal == 0)
		return (NULL);
	philo->last_time_eat = time_now();
	philo->start = philo->last_time_eat;
	while (1)
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
}