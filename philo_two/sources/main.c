/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/20 00:37:33 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "includes/main.h"
#include "includes/npc.h"
#include "includes/utils.h"
#include <fcntl.h>
#include <sys/stat.h>

sem_t			*create_sem(char *name, int value)
{
	sem_t	*ret;

	sem_unlink(name);
	ret = sem_open(name, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR, value);
	return (ret);
}

sem_t			*create_sem_id(size_t id, int value)
{
	size_t	size;
	char	*name;
	char	*ptr;
	sem_t	*ret;

	size = ft_strlen("philo ") + nbrlen(id);
	if (!(name = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	name[size] = 0;
	ptr = name;
	fill_str(&ptr, "philo ");
	fill_nbr(&ptr, id);
	ret = create_sem(name, value);
	free(name);
	return (ret);
}

t_philosopher	*init(t_parameters *parameters,
	sem_t *forks, t_dead *dead)
{
	size_t			amount;
	sem_t			**eat;
	t_philosopher	*philosophers;
	t_philosopher	*next;

	if (!(eat = malloc(sizeof(sem_t *)
		* parameters->number_of_philosophers)))
		return (NULL);
	amount = parameters->number_of_philosophers;
	while (amount--)
		eat[amount] = create_sem_id(amount + 1, 0);
	sem_post(*eat);
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
	t_dead			*dead;
	t_parameters	*parameters;
	sem_t			*forks;
	t_philosopher	*philosophers;

	if (!(dead = malloc(sizeof(t_dead))))
		return (1);
	dead->is = false;
	parameters = NULL;
	forks = NULL;
	philosophers = NULL;
	sem_unlink("forks");
	if (!(parameters = parse(argc, argv))
		|| !(dead->alive = create_sem("alive", 0))
		|| !(forks = create_sem("forks",
		parameters->number_of_philosophers))
		|| !(philosophers = init(parameters, forks, dead)))
		return (clean(parameters, philosophers, forks));
	spawn_all(philosophers);
	sem_wait(dead->alive);
	clean(parameters, philosophers, forks);
	return (0);
}
