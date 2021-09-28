/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:45:53 by yhebbat           #+#    #+#             */
/*   Updated: 2021/09/28 16:45:54 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_args *args)
{
	write(1, "arguments are not valid\n", 24);
	free(args);
	exit(0);
}

void	start(t_args *args)
{
	int		i;
	t_philo	*philo;

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
	destiny(args, philo);
}

int	main(int ac, char **av)
{
	t_args	*args;

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
