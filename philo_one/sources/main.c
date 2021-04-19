/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/20 01:02:02 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "includes/main.h"
#include "includes/npc.h"

t_philosopher	*init(t_parameters *parameters,
	pthread_mutex_t *forks, pthread_mutex_t *eat, t_dead *dead)
{
	size_t			amount;
	t_philosopher	*philosophers;
	t_philosopher	*next;

	amount = parameters->number_of_philosophers;
	while (amount--)
	{
		if (pthread_mutex_init(forks + amount, NULL)
			|| pthread_mutex_init(eat + amount, NULL))
			return (NULL);
		pthread_mutex_lock(eat + amount);
	}
	pthread_mutex_unlock(eat);
	if (pthread_mutex_init(dead->alive, NULL)
		|| !(philosophers = init_philosophers(parameters,
		forks, parameters->number_of_philosophers)))
		return (NULL);
	next = philosophers;
	while (next)
	{
		next->eat = eat;
		next->dead = dead;
		next = next->next;
	}
	return (philosophers);
}

int				main(int argc, char **argv)
{
	t_dead			*dead;
	t_parameters	*parameters;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eat;
	t_philosopher	*philosophers;

	if (!(dead = malloc(sizeof(t_dead))))
		return (1);
	dead->is = false;
	parameters = NULL;
	forks = NULL;
	philosophers = NULL;
	if (!(parameters = parse(argc, argv))
		|| !(dead->alive = malloc(sizeof(pthread_mutex_t)))
		|| !(forks = malloc(sizeof(pthread_mutex_t)
		* parameters->number_of_philosophers))
		|| !(eat = malloc(sizeof(pthread_mutex_t)
		* parameters->number_of_philosophers))
		|| !(philosophers = init(parameters, forks, eat, dead)))
		return (clean(parameters, philosophers, forks));
	spawn_all(philosophers);
	pthread_mutex_lock(dead->alive);
	pthread_mutex_lock(dead->alive);
	clean(parameters, philosophers, forks);
	return (0);
}
