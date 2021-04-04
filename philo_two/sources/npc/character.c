/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:48:19 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/04 23:40:15 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/npc.h"

void	wait_eat(t_philosopher *philosopher)
{
	sem_wait(philosopher->forks);
	console_log(philosopher->millis,
		philosopher->id, "has taken a fork");
	sem_wait(philosopher->forks);
	console_log(philosopher->millis,
		philosopher->id, "has taken a fork");
}

bool	action(t_philosopher *philosopher, size_t *last)
{
	console_log(philosopher->millis,
		philosopher->id, "is eating");
	usleep(philosopher->parameters->time_to_eat * 1000);
	philosopher->eat_count++;
	if (philosopher->eat_count >= philosopher->
		parameters->number_of_times_each_philosopher_must_eat)
		return (false);
	if (sem_post(philosopher->forks) || sem_post(philosopher->forks))
		return (false);
	philosopher->millis += philosopher->parameters->time_to_eat;
	*last = philosopher->millis;
	console_log(philosopher->millis,
		philosopher->id, "is sleeping");
	usleep(philosopher->parameters->time_to_sleep * 1000);
	philosopher->millis += philosopher->parameters->time_to_sleep;
	console_log(philosopher->millis,
		philosopher->id, "is thinking");
	return (true);
}

void	*spawn(void *ptr)
{
	t_philosopher	*philosopher;
	struct timeval	temp;
	size_t			last_millis;

	last_millis = 0;
	philosopher = ptr;
	while (!*philosopher->dead)
	{
		wait_eat(philosopher);
		if (gettimeofday(&temp, NULL))
			break ;
		philosopher->millis = (temp.tv_sec -
			philosopher->parameters->start.tv_sec) * 1000 + (temp.tv_usec
			- philosopher->parameters->start.tv_usec) / 1000;
		if (philosopher->millis - last_millis
			>= philosopher->parameters->time_to_die)
			break ;
		if (!action(philosopher, &last_millis))
			break ;
	}
	console_log(philosopher->millis, philosopher->id, "died");
	*philosopher->dead = true;
	return (NULL);
}
