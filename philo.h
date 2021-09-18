#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef	struct	s_args
{
	long				number_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				num_meal;
	unsigned long long	current_time;
	pthread_mutex_t 	*forks;
	pthread_mutex_t 	write;
	pthread_mutex_t		is_eating;
	struct t_philo 		*philo;
}t_args;

typedef struct s_philo
{
	pthread_t			tr;
	int					philo_id;
	unsigned long long	last_time_eat;
	int					nb_of_meals;
	int					eat;
	t_args				*args;
}t_philo;
