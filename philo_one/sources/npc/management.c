/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:34:23 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/04 22:36:30 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/philosophers.h"
#include "../includes/npc.h"

t_fork			*init_forks(size_t amount)
{
	t_fork	*forks;

	if (!(forks = malloc(sizeof(t_fork) * amount)))
		return (NULL);
	while (amount--)
	{
		pthread_mutex_init(&forks[amount].mutex, NULL);
		forks[amount].taken = false;
	}
	return (forks);
}

t_philosopher	*init_philosophers(t_parameters *parameters, t_fork *forks,
	bool *dead, size_t amount)
{
	t_philosopher	*philosopher;

	if (!(philosopher = malloc(sizeof(t_philosopher))))
		return (NULL);
	philosopher->id = amount;
	philosopher->parameters = parameters;
	if (parameters->number_of_philosophers == amount)
		philosopher->fork_right = forks;
	else
		philosopher->fork_right = forks + amount;
	philosopher->fork_left = forks + amount - 1;
	philosopher->eat_count = 0;
	philosopher->millis = 0;
	philosopher->dead = dead;
	philosopher->next = NULL;
	if (--amount)
		philosopher->next = init_philosophers(parameters, forks, dead, amount);
	return (philosopher);
}

void			spawn_all(t_philosopher *philosopher)
{
	if (philosopher->next)
		spawn_all(philosopher->next);
	if (!(philosopher->thread = malloc(sizeof(pthread_t))))
		return ;
	pthread_create(philosopher->thread, NULL, spawn, philosopher);
	pthread_detach(*philosopher->thread);
}
