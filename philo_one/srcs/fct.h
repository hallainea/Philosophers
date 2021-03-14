/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 07:14:22 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/14 18:50:32 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FCT_H
# define FCT_H

# include "philo.h"

t_arg	*parse(char **args);
void	*philosopher(void *ptr);
#endif
