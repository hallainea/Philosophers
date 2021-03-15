/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 21:47:30 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/15 13:57:29 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

# include <pthread.h>

typedef struct	s_arg
{
	int			amount;
	int			die;
	int			eat;
	int			sleep;
	int			max_eat;
	pthread_t	*threads;
}				t_arg;
#endif
