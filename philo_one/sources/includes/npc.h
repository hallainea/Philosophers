/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/19 19:09:28 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPC_H
# define NPC_H

# include "../includes/philosophers.h"

t_philosopher	*init_philosophers(t_parameters *parameters,
	pthread_mutex_t *forks, size_t amount);
void			spawn_all(t_philosopher *philosophers);
void			*spawn(void *ptr);
void			console_log(t_philosopher *philosopher, char *str);
#endif
