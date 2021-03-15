/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 07:10:55 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/15 14:05:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "arg.h"
#include "../utils/lib.h"

t_arg	*parse(char **args)
{
	t_arg	*arg;

	if (!(arg = malloc(sizeof(t_arg))))
		return (0);
	arg->amount = ft_atoi(*args++);
	arg->die = ft_atoi(*args++);
	arg->eat = ft_atoi(*args++);
	arg->sleep = ft_atoi(*args++);
	if (*args)
		arg->max_eat = ft_atoi(*args++);
	else
		arg->max_eat = -1;
	if (!(arg->threads = malloc(sizeof(pthread_t) * (arg->amount))))
		return (0);
	return (arg);
}
