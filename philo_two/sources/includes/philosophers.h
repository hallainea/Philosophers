/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:29:07 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/18 20:05:39 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>
# include "parameters.h"

typedef struct	s_philosopher
{
	size_t					id;
	t_parameters			*parameters;
	sem_t					*forks;
	sem_t					**eat;
	size_t					eat_count;
	size_t					millis;
	size_t					last_eat;
	bool					thinking;
	bool					*dead;
	struct s_philosopher	*next;
	pthread_t				*thread;
}				t_philosopher;

void			*spawn(void *ptr);
#endif
