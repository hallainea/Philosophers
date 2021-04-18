/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:29:36 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/18 20:54:38 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

size_t	ft_strlen(char *str);
int		ft_atos(char *str, size_t *to);
char	*ft_itoa(int n);
#endif
