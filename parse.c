#include "philo.h"

int		parsing(int ac, char **av, t_args *args)
{
	if (is_good_to_parse(av))
	{
		args->number_philo = ft_atoi(av[1]);
		args->time_die = ft_atoi(av[2]);
		args->time_eat = ft_atoi(av[3]);
		args->time_sleep = ft_atoi(av[4]);
		if (ac == 6)
			args->num_meal = ft_atoi(av[5]);
		else
			args->num_meal = -1;
	}
	return (is_good_to_parse(av));
}