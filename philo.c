#include "philo.h"
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// void    *func1(void *arg)
// {
//     int i;

//     i = 0;
//     pthread_mutex_lock(&mutex);
//     while (i < 100)
//     {
//         printf("%s\n", (char*)arg);
//         i++;
//     }
//     // printf("\n");
//     pthread_mutex_unlock(&mutex);
//     pthread_exit(arg);
// }

// void    *func2(void *arg)
// {
//     int i;

//     i = 0;
//     pthread_mutex_lock(&mutex);
//     while (i < 100)
//     {
//         printf("%s\n", (char *)arg);
//         i++;
//     }
//     printf("\n");
//     pthread_mutex_unlock(&mutex);
//     pthread_exit(arg);
// }

// int main(void)
// {
//     pthread_t t1;
//     pthread_t t2;
//     char      *s1;
//     char      *s2;

//     pthread_create(&t1, NULL, func1, "yassine");
//     pthread_create(&t2, NULL, func2, "hebbat");
//     pthread_join(t1,(void **)&s1);
//     pthread_join(t2,(void **)&s2);
//     printf("%s-------------%s\n", s1, s2);
// }

// #include <pthread.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// typedef	struct              s_p
// {
//     pthread_mutex_t         mutex;
//     int                     i;
// }                           t_p;

// // int ft_strlen(char *str)
// // {
// //     int i = 0;
// //     while (str[i])
// //         i++;
// //     return (i);
// // }

// void    *go1(void *pp)
// {
//     char *str;
//     int i = 0;
//     t_p *ppp;

//     ppp = (t_p *)pp;
//     str = "tread 1 : coucou ca va ? \n";
//     pthread_mutex_lock(&ppp->mutex); // si on enleve ici
//     while (str[i])
//     {
//         write(1, &str[i], 1);
//         i++;
//     }
//     pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
//     return (NULL);
// }

// int main()
// {
//     pthread_t               thread_id1;
//     pthread_t               thread_id2;
//     t_p                     p;
//     t_p                     *pp;

//     pp = (malloc(sizeof(t_p) * 1));
//     pp = &p;
//     p.i = 3;

//     pthread_mutex_init(&p.mutex, NULL);			// obligatoire de init le mutex
//     pthread_create(&thread_id1, NULL, go1, (void *)pp);
//     pthread_create(&thread_id2, NULL, go1, (void *)pp);
//     sleep(1);
// 	// free(pp);
// }

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

int		parsing(int ac, char **av, t_both both)
{
	if (is_good_to_parse(av))
	{
		both.args->number_philo = ft_atoi(av[1]);
		both.args->time_die = ft_atoi(av[2]);
		both.args->time_eat = ft_atoi(av[3]);
		both.args->time_sleep = ft_atoi(av[4]);
		if (ac == 6)
			both.args->num_meal = ft_atoi(av[5]);
		else
			both.args->num_meal = -1;
	}
	return (is_good_to_parse(av));
}

void	ft_exit(t_both both)
{
	write(1,"arguments are not valid\n",24);
	free(both.args);
	exit(0);
}

int main(int ac, char **av)
{
	t_both both;

    if (ac == 5 || ac == 6)
    {
		both.args = malloc(sizeof(t_args));
		if (!parsing(ac, av, both))
			ft_exit(both);
		both.philo = malloc(sizeof(t_philo) * both.args->number_philo);
    }
    else
       printf("this project take five or six arguments\n");
    return (0);
}