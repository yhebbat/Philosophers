#include "philo.h"

// void	eat(t_philo *philo)
// {
// 	int	right;
// 	int	left;

	// if (philo->philo_id % 2 == 0)
	// 	right = (philo->philo_id + 1) % (philo->args->number_philo);
	// else
	// 	right = philo->philo_id;
	// if (philo->philo_id % 2 == 0)
	// 	left = philo->philo_id;
	// else
	// 	left = (philo->philo_id + 1) % (philo->args->number_philo);
// 	if (pthread_mutex_lock(&philo->args->forks[left]) == 0)
// 		print(philo, FORK, time_passed(philo->start));
// 	if (pthread_mutex_lock(&philo->args->forks[right]) == 0)
// 		print(philo, FORK, time_passed(philo->start));
// 	philo->eat = 1;
// 	if (pthread_mutex_lock(&philo->args->is_eating) == 0)
// 	{
// 		print(philo, EAT, time_passed(philo->start));
// 		usleep((philo->args->time_eat * 1000));
// 		pthread_mutex_unlock(&philo->args->is_eating);
// 	}
// 	pthread_mutex_unlock(&philo->args->forks[left]);
// 	pthread_mutex_unlock(&philo->args->forks[right]);

// }

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
	// t_philo		*philo;

	// philo = (t_philo *)philostruct;
	// if (philo == NULL || philo->args->num_meal == 0)
	// 	return (NULL);
	// philo->start = philo->args->current_time;
	// philo->last_time_eat = time_now();
	// while (1)
	// {	
	// 	// if (philo->philo_id % 2 == 0)
	// 	// 	sleepu(150);
	// 	eat(philo);
	// 	ft_sleep(philo);
	// 	think(philo);
	// }

	t_philo		*philo;
	int			right;
	int			left;

	philo = (t_philo *)philostruct;
	if (philo == NULL || philo->args->num_meal == 0)
		return (NULL);
	philo->last_time_eat = time_now();
	philo->start = philo->last_time_eat;
	while (1)
	{
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
		pthread_mutex_lock(&philo->args->is_eating);
		philo->last_time_eat = time_now();
		pthread_mutex_unlock(&philo->args->is_eating);
		philo->eat = 1;
		print(philo, EAT, time_passed(philo->start));
		usleep((philo->args->time_eat * 1000) - 10000);
		sleepu(philo->last_time_eat + philo->args->time_eat);
		pthread_mutex_lock(&philo->args->is_eating);
		philo->eat = 0;
		pthread_mutex_unlock(&philo->args->is_eating);
		pthread_mutex_unlock(&philo->args->forks[left]);
		pthread_mutex_unlock(&philo->args->forks[right]);
		if (philo->args->num_meal > 0)
			philo->args->num_meal--;
		ft_sleep(philo);
		think(philo);
	}
}