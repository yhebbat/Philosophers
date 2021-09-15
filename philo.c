#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - '0');
	return (sum);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		is_good_to_parse(char **av)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if(av[i][j] > '9' || av[i][j] < '0' || ft_strlen(av[i]) > 10)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		parsing(int ac, char **av, t_args *args)
{
	int i;

	i = -1;
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
	while (++i < args->number_philo)
		pthread_mutex_init(&args->forks[i], NULL);
	return (is_good_to_parse(av));
}

void	ft_exit(t_args *args)
{
	write(1,"arguments are not valid\n",24);
	free(args);
	exit(0);
}

void	ft_lock_forks(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->args->number_philo)
	{
		if (i % 2)
		{
			if(pthread_mutex_lock(&philo->args->forks[i]))
				printf("error\n");
		}
		i++;
	}
}

void	routine(void	*param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	ft_lock_forks(philo);
}

void	create_create(t_philo *philo, t_args *args)
{
	int i;

	i = -1;
	while (++i < args->number_philo)
	{
		if (pthread_create(&philo[i].id, NULL, routine, &philo[i]))
            printf("error\n");
	}
}

int main(int ac, char **av)
{
	t_args *args;
	t_philo *philo;

	args = NULL;
	philo = NULL;
    if (ac == 5 || ac == 6)
    {
		args = malloc(sizeof(t_args));
		if (!parsing(ac, av, args))
			ft_exit(args);
		philo = malloc(sizeof(t_philo) * args->number_philo);
		create_create(philo, args);
    }
    else
       printf("this project take five or six arguments\n");
    return (0);
}