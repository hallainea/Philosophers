/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:58:05 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/15 13:52:59 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include "arg.h"

typedef struct	s_fork
{
	bool	taken;
}				t_fork;

typedef	struct	s_philo
{
	bool			*dead;
	int				id;
	pthread_mutex_t	*mutex;
	t_arg			*arg;
	t_fork			*left;
	t_fork			*right;
}				t_philo;
#endif
