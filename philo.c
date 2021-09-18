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
	pthread_mutex_init(&args->is_eating, NULL);
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

int		print(t_philo *philo, int to_write, unsigned long long time_ms)
{
	if (pthread_mutex_lock(&philo->args->write))
		return (1);
	if (to_write == DIE)
	{
		printf("%llu %d died\n", time_ms, philo->philo_id);
		return (1);
	}
	else if (to_write == EAT)
		printf("%llu %d is eating\n", time_ms, philo->philo_id);
	else if (to_write == SLEEP)
		printf("%llu %d is sleeping\n", time_ms, philo->philo_id);
	else if (to_write == FORK)
		printf("%llu %d has taken a fork\n", time_ms, philo->philo_id);
	else if (to_write == THINK)
		printf("%llu %d is thinking\n", time_ms, philo->philo_id);
	if (pthread_mutex_unlock(&philo->args->write))
		return (1);
	return (0);
}

unsigned long long	time_passed(unsigned long long start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (((end.tv_sec * 1000) + (end.tv_usec / 1000))
		- start);
}

void	eat(t_philo *philo)
{
	// int	right;
	int	left;

	// right = philo->philo_id - 1;
	left = philo->philo_id % philo->args->number_philo;
	pthread_mutex_lock(&philo->args->forks[left]);
	print(philo, FORK, time_passed(philo->last_time_eat));
	pthread_mutex_lock(&philo->args->forks[philo->philo_id - 1]);
	print(philo, FORK, time_passed(philo->last_time_eat));
	philo->eat = 1;
	pthread_mutex_lock(&philo->args->is_eating);
	usleep((philo->args->time_eat * 1000));
	print(philo, EAT, time_passed(philo->last_time_eat));
	pthread_mutex_unlock(&philo->args->is_eating);
}

void	sleep(t_philo *philo)
{
	print(philo, SLEEP, time_passed(philo->args->current_time));
	usleep(philo->args->time_sleep);
}

void	think(t_philo *philo)
{
	print(philo, THINK, time_passed(philo->args->current_time));
	// usleep(philo->args->time_sleep);
}

void	*work(void	*philostruct)
{
	t_philo		*philo;

	philo = (t_philo *)philostruct;
	if (philo == NULL || philo->args->num_meal == 0)
		return (NULL);
	philo->last_time_eat = time_now();
	while (1)
	{	
		if (philo->philo_id % 2 == 0)
			usleep(150);
		eat(philo);
		sleep(philo);
		think(philo);
	}
}

t_philo *init_philo(t_args *args)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * args->number_philo);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < args->number_philo)
	{
		philo[i].args = args;
		philo[i].philo_id = i + 1;
		philo[i].nb_of_meals = args->num_meal;
		philo[i].eat = 0;
	}
	return (philo);
}

unsigned long long time_now(void)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
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
		// philo[i].last_time_eat = time_now();
		if (pthread_create(&philo[i].tr, NULL, work, &philo[i]))
			printf("error\n");
		usleep(100);
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
		start(args);
    }
    else
       printf("this project take five or six arguments\n");
	free(args);
    return (0);
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
