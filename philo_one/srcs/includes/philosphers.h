/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:29:07 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/02 23:05:44 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include "fork.h"
# include "parameters.h"

typedef struct	s_philosopher
{
	size_t					id;
	t_parameters			*parameters;
	t_fork					*fork_left;
	t_fork					*fork_right;
	size_t					eat_count;
	bool					*dead;
	struct s_philosopher	*next;
	pthread_t				*thread;
}				t_philosopher;

void	*spawn(void *ptr);
#endif
