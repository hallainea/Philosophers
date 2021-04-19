/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:34:23 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/20 00:47:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/philosophers.h"
#include "../includes/npc.h"

t_philosopher	*init_philosophers(t_parameters *parameters,
	pthread_mutex_t *forks, size_t amount)
{
	t_philosopher	*philosopher;

	if (!(philosopher = malloc(sizeof(t_philosopher))))
		return (NULL);
	philosopher->id = parameters->number_of_philosophers - amount + 1;
	philosopher->parameters = parameters;
	if (parameters->number_of_philosophers == amount)
		philosopher->fork_right = forks;
	else
		philosopher->fork_right = forks + amount;
	philosopher->fork_left = forks + amount - 1;
	philosopher->eat_count = 0;
	philosopher->millis = 0;
	philosopher->last_eat = 0;
	philosopher->next = NULL;
	if (--amount)
		philosopher->next = init_philosophers(parameters, forks, amount);
	return (philosopher);
}

void			spawn_all(t_philosopher *philosophers)
{
	while (philosophers)
	{
		if (!(philosophers->thread = malloc(sizeof(pthread_t))))
			return ;
		pthread_create(philosophers->thread, NULL, spawn, philosophers);
		philosophers = philosophers->next;
	}
}
