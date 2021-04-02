/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:37:07 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/02 21:58:24 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "philosphers.h"

t_parameters	*parse(int argc, char **argv);
t_fork			*init_forks(size_t amount);
t_philosopher	*init_philosophers(t_parameters *parameters, t_fork *forks,
	bool *dead, size_t amount);
void			spawn_all(t_philosopher *philosopher);
#endif
