/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 21:54:08 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/14 19:02:12 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "fct.h"

t_philo	*create_philo(t_arg *arg, t_fork *fork)
{
	t_philo			*philo;
	pthread_mutex_t	mutex;
	int				index;

	if (!(philo = malloc(sizeof(t_philo) * arg->amount)))
		return (0);
	pthread_mutex_init(&mutex, NULL);
	index = arg->amount;
	while (index--)
	{
		philo[index].dead = false;
		philo[index].id = index;
		philo[index].mutex = &mutex;
		philo[index].arg = arg;
		philo[index].left = fork + index;
		if (index == arg->amount - 1)
			philo[index].right = fork;
		else
			philo[index].right = fork + index + 1;
		pthread_create(arg->threads + index, NULL, philosopher, philo + index);
	}
	return (philo);
}

int		main(int argc, char **argv)
{
	t_arg	*arg;
	t_fork	*fork;
	t_philo	*philo;
	int		index;

	if (argc < 5 || argc > 6)
		return (1);
	arg = parse(argv + 1);
	if (!(fork = malloc(sizeof(t_fork) * arg->amount)))
		return (0);
	index = arg->amount;
	while (index--)
		fork[index].taken = false;
	philo = create_philo(arg, fork);
	while (philo)
	{
		index = arg->amount;
		while (index--)
			if (philo[index].dead)
				return (0);
	}
	return (0);
}
