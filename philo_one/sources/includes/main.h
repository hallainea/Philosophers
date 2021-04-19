/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:37:07 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/19 20:00:19 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "philosophers.h"

t_parameters	*parse(int argc, char **argv);
int				clean(t_parameters *parameters,
	t_philosopher *philosophers, pthread_mutex_t *forks);
#endif
