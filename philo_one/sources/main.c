/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/05 01:51:44 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "includes/main.h"
#include "includes/npc.h"

int		clean(bool *dead, t_parameters *parameters, pthread_mutex_t *forks,
	t_philosopher *philosophers)
{
	t_philosopher	*tmp;

	free(dead);
	if (forks)
	{
		while (philosophers->parameters->number_of_philosophers--)
			pthread_mutex_destroy(&forks[philosophers->
				parameters->number_of_philosophers]);
		free(forks);
	}
	if (parameters)
		free(parameters);
	while (philosophers)
	{
		tmp = philosophers->next;
		free(philosophers->thread);
		free(philosophers);
		philosophers = tmp;
	}
	return (1);
}

#include <stdio.h>

void	alive(t_philosopher *philosophers)
{
	t_philosopher	*next;
	struct timeval	current;
	size_t			millis;

	
	if (gettimeofday(&current, NULL))
		return ;
	millis = (current.tv_sec - philosophers->parameters->start.tv_sec) * 1000 +
			(current.tv_usec - philosophers->parameters->start.tv_usec) / 1000;
	next = philosophers;
	while (next)
	{
		if (next->thinking)
		{
			next->millis = millis;
			if (next->millis - next->last_eat >= next->parameters->time_to_die)
			{
				*next->dead = true;
				console_log(next->millis, next->id, "died");
				break;
			}
		}
		next = next->next;
	}
	if (!*philosophers->dead)
	{
		usleep(1000);
		alive(philosophers);
	}
}

int		main(int argc, char **argv)
{
	bool			*dead;
	t_parameters	*parameters;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;

	if (!(dead = malloc(sizeof(bool))))
		return (1);
	*dead = false;
	parameters = NULL;
	forks = NULL;
	philosophers = NULL;
	if (!(parameters = parse(argc, argv)))
		return (clean(dead, parameters, forks, philosophers));
	if (!(forks = malloc(sizeof(pthread_mutex_t) * parameters->number_of_philosophers)))
		return (1);
	if (!(philosophers = init_philosophers(parameters,
			forks, dead, parameters->number_of_philosophers)))
		return (clean(dead, parameters, forks, philosophers));
	spawn_all(philosophers);
	alive(philosophers);
	clean(dead, parameters, forks, philosophers);
	return (0);
}
