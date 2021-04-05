/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/05 04:53:43 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "includes/main.h"
#include "includes/npc.h"

int				clean(bool *dead, t_parameters *parameters,
	sem_t *forks, t_philosopher *philosophers)
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

int				main(int argc, char **argv)
{
	bool			*dead;
	t_parameters	*parameters;
	t_philosopher	*philosophers;
	sem_t			*forks;

	if (!(dead = malloc(sizeof(bool))))
		return (1);
	*dead = false;
	parameters = NULL;
	philosophers = NULL;
	forks = NULL;
	sem_unlink("forks");
	if (!(parameters = parse(argc, argv))
		|| !(forks = sem_open("forks",
		O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR,
		parameters->number_of_philosophers))
		|| !(philosophers = init_philosophers(parameters,
			forks, dead, parameters->number_of_philosophers)))
		return (clean(dead, parameters, forks, philosophers));
	spawn_all(philosophers);
	alive(philosophers);
	clean(dead, parameters, forks, philosophers);
	return (0);
}
