/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:48:19 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/20 01:00:33 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/npc.h"

bool	take_fork(t_philosopher *philosopher, pthread_mutex_t *fork)
{
	struct timeval	current;
	size_t			millis;

	if (philosopher->dead->is)
		return (false);
	pthread_mutex_lock(fork);
	if (gettimeofday(&current, NULL))
		return (false);
	millis = (current.tv_sec - philosopher->parameters->start.tv_sec) * 1000
		+ (current.tv_usec - philosopher->parameters->start.tv_usec) / 1000;
	if (millis - philosopher->last_eat >= philosopher->parameters->time_to_die)
	{
		philosopher->millis = philosopher->last_eat
			+ philosopher->parameters->time_to_die;
		return (false);
	}
	philosopher->millis = millis;
	console_log(philosopher, "has taken a fork");
	return (true);
}

bool	action(t_philosopher *philosopher)
{
	console_log(philosopher, "is eating");
	usleep(philosopher->parameters->time_to_eat * 1000);
	pthread_mutex_unlock(philosopher->fork_left);
	pthread_mutex_unlock(philosopher->fork_right);
	philosopher->eat_count++;
	if (philosopher->eat_count >= philosopher->
		parameters->number_of_times_each_philosopher_must_eat)
		return (false);
	philosopher->millis += philosopher->parameters->time_to_eat;
	philosopher->last_eat = philosopher->millis;
	console_log(philosopher, "is sleeping");
	usleep(philosopher->parameters->time_to_sleep * 1000);
	philosopher->millis += philosopher->parameters->time_to_sleep;
	console_log(philosopher, "is thinking");
	return (true);
}

void	*spawn(void *ptr)
{
	t_philosopher	*philosopher;
	size_t			next;

	philosopher = ptr;
	while (!philosopher->dead->is)
	{
		pthread_mutex_lock(philosopher->eat + (philosopher->id - 1));
		if (!(take_fork(philosopher, philosopher->fork_left)
			&& take_fork(philosopher, philosopher->fork_right)))
			break ;
		next = philosopher->id + 1;
		if (next >= philosopher->parameters->number_of_philosophers)
			next = philosopher->id % 2;
		pthread_mutex_unlock(philosopher->eat + next);
		if (!action(philosopher))
			break ;
	}
	console_log(philosopher, "died");
	philosopher->dead->is = true;
	pthread_mutex_unlock(philosopher->dead->alive);
	return (NULL);
}
