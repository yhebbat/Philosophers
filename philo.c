#include "philo.h"

void	ft_exit(t_args *args)
{
	write(1,"arguments are not valid\n",24);
	free(args);
	exit(0);
}

// void	ft_free(t_args *args, t_philo *philo)
// {
// 	int i;

// 	if (args != NULL && philo != NULL)
// 	{
// 		i = 0;
// 		while (i < args->number_philo)
// 		{
// 			printf("sss\n");
// 			free(args->forks[i]);
// 			free(&philo[i]);
// 			i++;
// 		}
// 		free(philo);
// 		free(args);
// 	}
// }

int		ft_checkmeals(t_args *args, t_philo *philo)
{
	if (args->num_meal != -1)
	{
		if (args->num_meal == 0)
		{
			print(philo, DIE, 0);
			return (1);
		}
		if (philo->nb_of_meals == 0 && philo->eat == 0)
		{
			print(philo, DIE, time_passed(philo->start));
			return (1);
		}
	}
	return (0);
}

void	diedie(t_args *args ,t_philo *philo)
{
	int i;
	int k;

	k = 1;
	while (k)
	{
		i = 0;
		while (i < args->number_philo && !philo->eat)
		{
			pthread_mutex_lock(&args->is_eating);
			if (ft_checkmeals(args, &philo[i]))
			{
				k = 0;
				break ;	
			}
			if (philo[i].eat == 0 &&
				time_passed(philo[i].last_time_eat) > (unsigned long long)args->time_die)
			{
				print(&philo[i], DIE, time_passed(philo[i].start));
				k = 0;
				break ;
			}
			pthread_mutex_unlock(&args->is_eating);
			i++;
		}	
	}
}

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
	diedie(args, philo);
	// ft_free(args, philo);
}

int main(int ac, char **av)
{
	t_args *args;

	args = NULL;
    if (ac == 5 || ac == 6)
    {
		args = malloc(sizeof(t_args));
		if (!parsing(ac, av, args))
			ft_exit(args);
		start(args);
    }
    else
       printf("this project take five or six arguments\n");
    return (0);
}