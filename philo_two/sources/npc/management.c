/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:34:23 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/04 23:29:36 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/philosophers.h"
#include "../includes/npc.h"

t_philosopher	*init_philosophers(t_parameters *parameters, sem_t *forks,
	bool *dead, size_t amount)
{
	t_philosopher	*philosopher;

	if (!(philosopher = malloc(sizeof(t_philosopher))))
		return (NULL);
	philosopher->id = amount;
	philosopher->parameters = parameters;
	philosopher->forks = forks;
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
