/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:48:19 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/19 10:02:20 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/npc.h"

bool	take_fork(t_philosopher *philosopher)
{
	sem_wait(philosopher->forks);
	if (*philosopher->dead)
		return (false);
	console_log(philosopher->millis,
		philosopher->id, "has taken a fork");
	return (true);
}

bool	action(t_philosopher *philosopher)
{
	philosopher->thinking = false;
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
	philosopher->last_eat = philosopher->millis;
	console_log(philosopher->millis,
		philosopher->id, "is sleeping");
	usleep(philosopher->parameters->time_to_sleep * 1000);
	philosopher->millis += philosopher->parameters->time_to_sleep;
	console_log(philosopher->millis,
		philosopher->id, "is thinking");
	philosopher->thinking = true;
	return (true);
}

void	*spawn(void *ptr)
{
	t_philosopher	*philosopher;
	size_t			next;

	philosopher = ptr;
	while (!*philosopher->dead)
	{
		sem_wait(philosopher->eat[philosopher->id - 1]);
		if (!take_fork(philosopher)
			|| !take_fork(philosopher))
			break ;
		next = philosopher->id + 1;
		if (next >= philosopher->parameters->number_of_philosophers)
			next = philosopher->id % 2;
		sem_post(philosopher->eat[next]);
		if (!action(philosopher))
			break ;
	}
	console_log(philosopher->millis, philosopher->id, "died");
	*philosopher->dead = true;
	return (NULL);
}
