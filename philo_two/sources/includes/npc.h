/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/19 09:42:23 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPC_H
# define NPC_H

# include "../includes/philosophers.h"

t_philosopher	*init_philosophers(t_parameters *parameters,
	size_t amount);
void			spawn_all(t_philosopher *philosophers);
void			*spawn(void *ptr);
void			console_log(size_t millis, size_t id, char *str);
size_t			nbrlen(size_t nbr);
void			fill_nbr(char **ptr, size_t nbr);
void			fill_str(char **ptr, char *str);
#endif
