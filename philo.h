#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef	struct	s_args
{
	long	number_philo;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	num_meal;
	// int		done;
	pthread_mutex_t *forks;
	pthread_mutex_t write;
	struct t_philo *philo;
}t_args;

typedef struct s_philo
{
	pthread_t id;
	int	philo_id;
	// pthread_mutex_t eat;
	unsigned long long last_time_eat;
	int is_eating;
	int nb_of_meals;
	t_args *args;
}t_philo;