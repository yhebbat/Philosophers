/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:46:03 by yhebbat           #+#    #+#             */
/*   Updated: 2021/09/28 16:46:04 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_helper(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->is_eating);
	philo->last_time_eat = time_now();
	pthread_mutex_unlock(&philo->args->is_eating);
	philo->eat = 1;
	print(philo, EAT, time_passed(philo->start));
	usleep((philo->args->time_eat * 1000) - 10000);
	sleepu(philo->last_time_eat + philo->args->time_eat);
	pthread_mutex_lock(&philo->args->is_eating);
	philo->eat = 0;
	philo->nb_of_meals++;
	if (philo->nb_of_meals == philo->args->num_meal)
		philo->args->all++;
	pthread_mutex_unlock(&philo->args->is_eating);
}

void	eat(t_philo *philo)
{
	int	right;
	int	left;

	if (philo->philo_id % 2 == 0)
		right = (philo->philo_id + 1) % (philo->args->number_philo);
	else
		right = philo->philo_id;
	if (philo->philo_id % 2 == 0)
		left = philo->philo_id;
	else
		left = (philo->philo_id + 1) % (philo->args->number_philo);
	pthread_mutex_lock(&philo->args->forks[left]);
	print(philo, FORK, time_passed(philo->start));
	pthread_mutex_lock(&philo->args->forks[right]);
	print(philo, FORK, time_passed(philo->start));
	eat_helper(philo);
	pthread_mutex_unlock(&philo->args->forks[left]);
	pthread_mutex_unlock(&philo->args->forks[right]);
}

void	ft_sleep(t_philo *philo)
{
	unsigned long long	before_sleep;

	before_sleep = time_now();
	print(philo, SLEEP, time_passed(philo->start));
	usleep((philo->args->time_sleep * 1000) - 10000);
	sleepu(philo->args->time_sleep + before_sleep);
}

void	think(t_philo *philo)
{
	print(philo, THINK, time_passed(philo->start));
}

void	*work(void	*philostruct)
{
	t_philo	*philo;

	philo = (t_philo *)philostruct;
	if (philo == NULL || philo->args->num_meal == 0)
		return (NULL);
	while (1)
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
}
