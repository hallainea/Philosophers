/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/18 22:32:20 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "includes/main.h"
#include "includes/npc.h"
#include "includes/utils.h"

int				clean(t_parameters *parameters,
	t_philosopher *philosophers, sem_t *forks)
{
	t_philosopher	*next;

	if (forks)
		sem_close(forks);
	if (philosophers)
	{
		/*while (philosophers->parameters->number_of_philosophers--)
			sem_close(philosophers->eat
				+ philosophers->parameters->number_of_philosophers);*/
		free(philosophers->eat);
		free(philosophers->dead);
	}
	if (parameters)
		free(parameters);
	while (philosophers)
	{
		next = philosophers->next;
		free(philosophers->thread);
		free(philosophers);
		philosophers = next;
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

t_philosopher	*init(t_parameters *parameters,
	sem_t *forks, bool *dead)
{
	size_t			amount;
	char			*name;
	sem_t			*eat;
	sem_t			*temp;
	t_philosopher	*philosophers;
	t_philosopher	*next;

	if (!(eat = malloc(sizeof(sem_t)
		* parameters->number_of_philosophers)))
		return (NULL);
	temp = eat;
	amount = parameters->number_of_philosophers;
	while (amount--)
	{
		name = ft_itoa(parameters->number_of_philosophers - amount - 1);
		sem_unlink(name);
		temp++;
		temp = sem_open(name, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR, 0);
	}
	sem_post(eat);
	if (!(philosophers = init_philosophers(parameters,
		parameters->number_of_philosophers)))
		return (NULL);
	next = philosophers;
	while (next)
	{
		next->forks = forks;
		next->eat = eat;
		next->dead = dead;
		next = next->next;
	}
	return (philosophers);
}

int				main(int argc, char **argv)
{
	bool			*dead;
	t_parameters	*parameters;
	sem_t			*forks;
	t_philosopher	*philosophers;

	if (!(dead = malloc(sizeof(bool))))
		return (1);
	*dead = false;
	parameters = NULL;
	forks = NULL;
	philosophers = NULL;
	sem_unlink("forks");
	if (!(parameters = parse(argc, argv))
		|| !(forks = sem_open("forks",
		O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR,
		parameters->number_of_philosophers))
		|| !(philosophers = init(parameters, forks, dead)))
		return (clean(parameters, philosophers, forks));
	spawn_all(philosophers);
	alive(philosophers);
	clean(parameters, philosophers, forks);
	return (0);
}
