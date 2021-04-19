/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 19:59:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/20 01:00:49 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/philosophers.h"

int				clean_loops(t_parameters *parameters,
	t_philosopher *philosophers, pthread_mutex_t *forks, pthread_mutex_t *eat)
{
	t_philosopher	*next;

	while (philosophers)
	{
		next = philosophers->next;
		pthread_mutex_unlock(philosophers->eat + (philosophers->id - 1));
		pthread_join(*philosophers->thread, NULL);
		free(philosophers->thread);
		free(philosophers);
		philosophers = next;
	}
	if (parameters)
	{
		while (parameters->number_of_philosophers--)
		{
			if (forks)
				pthread_mutex_destroy(forks
					+ parameters->number_of_philosophers);
			if (eat)
				pthread_mutex_destroy(eat
					+ parameters->number_of_philosophers);
		}
		free(parameters);
	}
	return (1);
}

int				clean(t_parameters *parameters,
	t_philosopher *philosophers, pthread_mutex_t *forks)
{
	pthread_mutex_t	*eat;
	t_dead			*dead;

	eat = NULL;
	dead = NULL;
	if (philosophers)
	{
		eat = philosophers->eat;
		dead = philosophers->dead;
	}
	clean_loops(parameters, philosophers, forks, eat);
	if (forks)
		free(forks);
	if (eat)
		free(eat);
	if (dead)
	{
		pthread_mutex_destroy(dead->alive);
		free(dead->alive);
		free(dead);
	}
	return (1);
}
