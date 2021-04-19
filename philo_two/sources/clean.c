/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 19:59:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/19 20:59:43 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/philosophers.h"

int				clean_loops(t_parameters *parameters,
	t_philosopher *philosophers, sem_t **eat)
{
	t_philosopher	*next;

	while (philosophers)
	{
		next = philosophers->next;
		sem_post(philosophers->eat[philosophers->id - 1]);
		pthread_join(*philosophers->thread, NULL);
		free(philosophers->thread);
		free(philosophers);
		philosophers = next;
	}
	if (parameters)
	{
		if (eat)
			while (parameters->number_of_philosophers--)
				sem_close(eat[parameters->number_of_philosophers]);
		free(parameters);
	}
	return (1);
}

int				clean(t_parameters *parameters,
	t_philosopher *philosophers, sem_t *forks)
{
	sem_t			**eat;
	bool			*dead;

	eat = NULL;
	dead = NULL;
	if (philosophers)
	{
		eat = philosophers->eat;
		dead = philosophers->dead;
	}
	clean_loops(parameters, philosophers, eat);
	if (forks)
		sem_close(forks);
	if (eat)
		free(eat);
	if (dead)
		free(dead);
	return (1);
}
