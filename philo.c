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

void	init_mutex(t_args *args)
{
	int i;

	i = -1;
	args->forks = malloc(args->number_philo * sizeof(pthread_mutex_t));
	while (++i < args->number_philo)
		pthread_mutex_init(&args->forks[i], NULL);
	pthread_mutex_init(&args->write, NULL);
}

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

void	ft_exit(t_args *args)
{
	write(1,"arguments are not valid\n",24);
	free(args);
	exit(0);
}

// void	ft_lock_forks(t_philo *philo)
// {
// 	int left;
// 	int right;

// 	if (philo->philo_id % 2)
// 		left =  philo->philo_id;
// 	else
// 		left = (philo->philo_id + 1) % (philo->args->number_philo);
// 	if (philo->philo_id % 2 == 0)
// 		right =  philo->philo_id;
// 	else
// 		right = (philo->philo_id + 1) % (philo->args->number_philo);
// 	pthread_mutex_lock(&philo->args->forks[left]);
// 	pthread_mutex_lock(&philo->args->forks[right]);
// }

void	*work(void	*param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	while (1)
	{	
		ft_lock_forks(philo);
		
	}
}

void	start(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;

	while (i < args->number_philo)
	{
		if (pthread_create(&philo[i].id, NULL, work, &philo[i]))
			printf("error\n");
		i++;
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
		init_mutex(args);
		philo = malloc(sizeof(t_philo) * args->number_philo);
		start(philo, args);
    }
    else
       printf("this project take five or six arguments\n");
    return (0);
}