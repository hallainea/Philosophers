/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/05 02:46:50 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "includes/main.h"
#include "includes/npc.h"

int				clean(bool *dead, t_parameters *parameters,
	pthread_mutex_t *forks, t_philosopher *philosophers)
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
		pthread_detach(*philosophers->thread);
		free(philosophers->thread);
		free(philosophers);
		philosophers = tmp;
	}
	return (1);
}

void			alive(t_philosopher *philosophers)
{
	t_philosopher	*next;
	struct timeval	current;
	size_t			millis;

	usleep(1000);
	if (gettimeofday(&current, NULL))
		return ;
	millis = (current.tv_sec - philosophers->parameters->start.tv_sec) * 1000 +
			(current.tv_usec - philosophers->parameters->start.tv_usec) / 1000;
	next = philosophers;
	while (next)
	{
		if (next->thinking)
			if ((next->millis = millis) - next->last_eat
				>= next->parameters->time_to_die)
			{
				*next->dead = true;
				console_log(next->millis, next->id, "died");
				break ;
			}
		next = next->next;
	}
	if (!*philosophers->dead)
		alive(philosophers);
}

t_philosopher	*init(bool *dead, t_parameters *parameters,
	pthread_mutex_t *forks)
{
	size_t	amount;

	amount = parameters->number_of_philosophers;
	while (amount--)
		if (pthread_mutex_init(&forks[amount], NULL))
			return (0);
	return (init_philosophers(parameters,
			forks, dead, parameters->number_of_philosophers));
}

int				main(int argc, char **argv)
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
	if (!(parameters = parse(argc, argv))
		|| !(forks = malloc(sizeof(pthread_mutex_t)
		* parameters->number_of_philosophers))
		|| !(philosophers = init(dead, parameters, forks)))
		return (clean(dead, parameters, forks, philosophers));
	spawn_all(philosophers);
	alive(philosophers);
	clean(dead, parameters, forks, philosophers);
	return (0);
}
