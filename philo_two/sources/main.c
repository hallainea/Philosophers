/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/04 23:39:19 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "includes/main.h"
#include "includes/npc.h"

int		clean(bool *dead, t_parameters *parameters, sem_t *forks,
	t_philosopher *philosophers)
{
	t_philosopher	*tmp;

	free(dead);
	if (forks)
		sem_close(forks);
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
	while (!*philosophers->dead)
		usleep(1000);
}

int		main(int argc, char **argv)
{
	bool			*dead;
	t_parameters	*parameters;
	sem_t 			*forks;
	t_philosopher	*philosophers;

	if (!(dead = malloc(sizeof(bool))))
		return (1);
	*dead = false;
	parameters = NULL;
	sem_unlink("forks");
	forks = NULL;
	philosophers = NULL;
	if (!((parameters = parse(argc, argv))
		&& (forks = sem_open("forks", O_CREAT, S_IRUSR | S_IWUSR, parameters->number_of_philosophers))
		&& (philosophers = init_philosophers(parameters,
			forks, dead, parameters->number_of_philosophers))))
		return (clean(dead, parameters, forks, philosophers));
	spawn_all(philosophers);
	alive(philosophers);
	clean(dead, parameters, forks, philosophers);
	return (0);
}
