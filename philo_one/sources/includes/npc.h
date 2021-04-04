/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/05 00:09:13 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPC_H
# define NPC_H

# include "../includes/philosophers.h"

t_philosopher	*init_philosophers(t_parameters *parameters, pthread_mutex_t *forks,
	bool *dead, size_t amount);
void			spawn_all(t_philosopher *philosophers);
void			*spawn(void *ptr);
void			console_log(size_t millis, size_t id, char *str);
#endif
