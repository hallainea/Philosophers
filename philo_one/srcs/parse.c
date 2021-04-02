/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:47:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/02 22:01:15 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include "includes/parameters.h"
#include "includes/utils.h"

t_parameters	*parse(int argc, char **argv)
{
	t_parameters	*parameters;

	if (!((argc == 5 || argc == 6)
		&& (parameters = malloc(sizeof(t_parameters)))))
		return (NULL);
	parameters->number_of_times_each_philosopher_must_eat = -1;
	if (ft_atos(argv[1], &parameters->number_of_philosophers)
		|| ft_atos(argv[2], &parameters->time_to_die)
		|| ft_atos(argv[3], &parameters->time_to_eat)
		|| ft_atos(argv[4], &parameters->time_to_sleep)
		|| (argc == 6 && ft_atos(argv[5], &parameters->number_of_times_each_philosopher_must_eat))
		|| gettimeofday(&parameters->start, NULL))
	{
		free(parameters);
		return (NULL);
	}
	return (parameters);
}