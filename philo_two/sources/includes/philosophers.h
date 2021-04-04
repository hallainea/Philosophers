/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:29:07 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/04 23:19:28 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <stdbool.h>
# include <pthread.h>
# include "parameters.h"

typedef struct	s_philosopher
{
	size_t					id;
	t_parameters			*parameters;
	sem_t					*forks;
	size_t					eat_count;
	size_t					millis;
	bool					*dead;
	struct s_philosopher	*next;
	pthread_t				*thread;
}				t_philosopher;

void			*spawn(void *ptr);
#endif
