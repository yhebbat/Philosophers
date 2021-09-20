#include "philo.h"

void	ft_exit(t_args *args)
{
	write(1,"arguments are not valid\n",24);
	free(args);
	exit(0);
}

// void	diedie(t_args *args ,t_philo *philo)
// {
// 	int i;

// 	while (args->num_meal != 0)
// 	{
// 		i = 0;
// 		while (i < args->number_philo)
// 		{
// 			pthread_mutex_lock(&args->is_eating);
// 			if (philo[i].eat == 0 && time_passed(philo[i].last_time_eat) > (unsigned long long)args->time_eat)
// 			{
// 				print(&philo[i], DIE, time_passed(philo[i].start));
// 				break ;
// 			}
// 			pthread_mutex_unlock(&args->is_eating);
// 			i++;
// 		}	
// 	}
	
// }

void	start(t_args *args)
{
	int	i;
	t_philo *philo;

	i = 0;
	init_mutex(args);
	philo = init_philo(args);
	args->current_time = time_now();
	while (i < args->number_philo)
	{
		if (pthread_create(&philo[i].tr, NULL, work, &philo[i]))
			printf("error\n");
		usleep(100);
		i++;
	}
	// diedie(args, philo);
	pthread_join((philo[0].tr), NULL);
}

int main(int ac, char **av)
{
	t_args *args;
	// t_philo *philo;

	args = NULL;
	// philo = NULL;
    if (ac == 5 || ac == 6)
    {
		args = malloc(sizeof(t_args));
		if (!parsing(ac, av, args))
			ft_exit(args);
		start(args);
    }
    else
       printf("this project take five or six arguments\n");
	// printf("%ld\n", args->number_philo);
	
	// free(args);
    return (0);
}