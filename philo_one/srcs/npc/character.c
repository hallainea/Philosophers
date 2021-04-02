/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:48:19 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/02 23:43:17 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/npc.h"

bool	can_eat(t_philosopher *philosopher)
{
	bool	ret;

	pthread_mutex_lock(&philosopher->fork_left->mutex);
	pthread_mutex_lock(&philosopher->fork_right->mutex);
	ret = false;
	if (!philosopher->fork_left->taken && !philosopher->fork_right->taken)
	{
		ret = true;
		philosopher->fork_left->taken = true;
		philosopher->fork_right->taken = true;
	}
	pthread_mutex_unlock(&philosopher->fork_left->mutex);
	pthread_mutex_unlock(&philosopher->fork_right->mutex);
	return (ret);
}

#include <stdio.h>

void	*spawn(void *ptr)
{
	t_philosopher	*philosopher;
	struct timeval	last;
	struct timeval	eat;
	size_t			millis;

	if (gettimeofday(&last, NULL))
		return (NULL);
	millis = 0;
	philosopher = ptr;
	while (!*philosopher->dead && millis < philosopher->parameters->time_to_die)
	{
		if (gettimeofday(&eat, NULL))
			break ;
		millis = (eat.tv_sec - last.tv_sec) * 1000 + (eat.tv_usec - last.tv_usec) / 1000;
		if (can_eat(philosopher))
		{
			console_log(philosopher->parameters->start, philosopher->id, "has taken a fork");
			if (gettimeofday(&eat, NULL))
				break;
			console_log(philosopher->parameters->start, philosopher->id, "is eating");
			usleep(philosopher->parameters->time_to_eat * 1000);
			philosopher->eat_count++;
			if (philosopher->eat_count >= philosopher->parameters->number_of_times_each_philosopher_must_eat)
				break;
			philosopher->fork_left->taken = false;
			philosopher->fork_right->taken = false;
			console_log(philosopher->parameters->start, philosopher->id, "is sleeping");
			usleep(philosopher->parameters->time_to_sleep * 1000);
			millis = (eat.tv_sec - last.tv_sec) * 1000 + (eat.tv_usec - last.tv_usec) / 1000;
			if (millis >= philosopher->parameters->time_to_die)
				break;
			if (gettimeofday(&last, NULL))
				break;
			console_log(philosopher->parameters->start, philosopher->id, "is thinking");
		}
	}
	*philosopher->dead = true;
	console_log(philosopher->parameters->start, philosopher->id, "died");
	return (NULL);
}