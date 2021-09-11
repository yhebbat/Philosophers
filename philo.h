#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct s_args
{
	int	number_philo;
	int	time_die;
	int	time_eat;
	int time_sleep;
	int	num_meal;
}t_args;

typedef struct s_philo
{
	int	philo_id;
	int left_f;
	int right_f;
}t_philo;

typedef struct s_both
{
	t_args *args;
	t_philo *philo;
}t_both;
