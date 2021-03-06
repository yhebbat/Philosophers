/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destiny.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:45:08 by yhebbat           #+#    #+#             */
/*   Updated: 2021/09/28 16:45:12 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checkmeals(t_args *args, t_philo *philo, int *k)
{
	if (args->num_meal != -1)
	{
		if (args->num_meal == 0)
		{
			*k = 0;
			return (1);
		}
		if (args->all == args->number_philo && philo->eat == 0)
		{
			*k = 0;
			return (1);
		}
	}
	return (0);
}

void	destiny(t_args	*args, t_philo	*philo)
{
	int	i;
	int	k;

	k = 1;
	while (k)
	{
		i = 0;
		while (i < args->number_philo && !philo->eat)
		{
			pthread_mutex_lock(&args->is_eating);
			if (ft_checkmeals(args, &philo[i], &k))
				break ;
			if (philo[i].eat == 0
				&& time_passed(philo[i].last_time_eat)
				> (unsigned long)args->time_die)
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
