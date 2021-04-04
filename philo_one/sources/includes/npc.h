/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/02 23:48:58 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPC_H
# define NPC_H

# include "../includes/philosophers.h"

t_fork			*init_forks(size_t amount);
t_philosopher	*init_philosophers(t_parameters *parameters, t_fork *forks,
	bool *dead, size_t amount);
void			spawn_all(t_philosopher *philosopher);
void			*spawn(void *ptr);
void			console_log(struct timeval start, size_t id, char *str);
#endif
