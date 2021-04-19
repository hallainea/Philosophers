/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:34:23 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/19 23:59:24 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/philosophers.h"
#include "../includes/npc.h"

t_philosopher	*init_philosophers(t_parameters *parameters,
	size_t amount)
{
	t_philosopher	*philosopher;

	if (!(philosopher = malloc(sizeof(t_philosopher))))
		return (NULL);
	philosopher->id = parameters->number_of_philosophers - amount + 1;
	philosopher->parameters = parameters;
	philosopher->eat_count = 0;
	philosopher->millis = 0;
	philosopher->last_eat = 0;
	philosopher->next = NULL;
	if (--amount)
		philosopher->next = init_philosophers(parameters, amount);
	return (philosopher);
}

void			spawn_all(t_philosopher *philosophers)
{
	pid_t	pid;

	while (philosophers)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (!pid)
		{
			spawn(philosophers);
			exit(0);
		}
		else
		{
			philosophers->pid = pid;
			philosophers = philosophers->next;
		}
	}
}
