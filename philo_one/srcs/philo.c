/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 07:19:15 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/14 18:54:28 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"
#include "../utils/lib.h"

void	action(t_philo philo, char *str, int millis)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld %d %s\n", time.tv_usec / 1000, philo.id, str);
	if (millis)
		usleep(millis * 1000);
}

bool	check(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	if (philo->left->taken || philo->right->taken)
	{
		pthread_mutex_unlock(philo->mutex);
		return (false);
	}
	philo->left->taken = true;
	philo->right->taken = true;
	pthread_mutex_unlock(philo->mutex);
	action(*philo, "has taken a fork", 0);
	return (true);
}

void	*philosopher(void *ptr)
{
	t_philo			*philo;
	int				old_timestamp;
	struct timeval	time;

	philo = ptr;
	while (!philo->dead)
		if (check(philo))
		{
			gettimeofday(&time, NULL);
			old_timestamp = time.tv_usec;
			action(*philo, "is eating", philo->arg->eat);
			pthread_mutex_lock(philo->mutex);
			philo->left->taken = false;
			philo->right->taken = false;
			pthread_mutex_unlock(philo->mutex);
			action(*philo, "is sleeping", philo->arg->sleep);
			gettimeofday(&time, NULL);
			if (time.tv_usec - old_timestamp >= philo->arg->die * 1000)
				break ;
			action(*philo, "is thinking", 0);
		}
	action(*philo, "died\n", 0);
	philo->dead = true;
	return (NULL);
}
