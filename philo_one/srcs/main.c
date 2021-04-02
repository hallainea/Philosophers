/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/02 23:44:39 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "includes/main.h"
#include "includes/npc.h"

int		clean(bool *dead, t_parameters *parameters, t_fork *forks,
	t_philosopher *philosophers)
{
	t_philosopher	*tmp;

	free(dead);
	if (forks)
	{
		while (philosophers->parameters->number_of_philosophers--)
			pthread_mutex_destroy(&forks[philosophers->parameters->number_of_philosophers].mutex);
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

void	alive(t_philosopher *philosophers)
{
	while (philosophers->next)
		philosophers = philosophers->next;
	pthread_join(*philosophers->thread, NULL);
}

int 	main(int argc, char **argv)
{
	bool			*dead;
	t_parameters	*parameters;
	t_fork			*forks;
	t_philosopher	*philosophers;

	if (!(dead = malloc(sizeof(bool))))
		return (1);
	*dead = false;
	parameters = NULL;
	forks = NULL;
	philosophers = NULL;
	if (!((parameters = parse(argc, argv))
		&& (forks = init_forks(parameters->number_of_philosophers))
		&& (philosophers = init_philosophers(parameters, forks, dead, parameters->number_of_philosophers))))
		return (clean(dead, parameters, forks, philosophers));
	spawn_all(philosophers);
	alive(philosophers);
	clean(dead, parameters, forks, philosophers);
	return (0);
}
