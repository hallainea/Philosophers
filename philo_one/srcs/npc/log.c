/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 22:17:38 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/02 22:55:23 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include "../includes/utils.h"

void	fill_nbr(char **ptr, size_t nbr)
{
	size_t	pow;
	size_t	temp;

	temp = nbr;
	pow = 10;
	while (temp /= 10)
		pow *= 10;
	while (pow /= 10)
		*(*ptr)++ = (nbr / pow) % 10 + '0';
}

void	fill_str(char **ptr, char *str)
{
	while (*str)
		*(*ptr)++ = *str++;
}

size_t	nbrlen(size_t nbr)
{
	size_t	len;
	size_t	temp;

	if (nbr == 0)
		return (1);
	len = 0;
	temp = nbr * 10;
	while (temp /= 10)
		len++;
	return (len);
}

#include <stdio.h>

void	console_log(struct timeval start, size_t id, char *str)
{
	struct timeval	tv;
	size_t			millis;
	size_t			length;
	char			*buffer;
	char			*ptr;

	if (gettimeofday(&tv, NULL))
		return ;
	millis = (tv.tv_sec - start.tv_sec) * 1000 + (tv.tv_usec - start.tv_usec) / 1000;
	length = 3 + ft_strlen(str) + nbrlen(millis) + nbrlen(id);
	if (!(buffer = malloc(sizeof(char) * length)))
		return ;
	ptr = buffer;
	fill_nbr(&ptr, millis);
	*ptr++ = ' ';
	fill_nbr(&ptr, id);
	*ptr++ = ' ';
	fill_str(&ptr, str);
	*ptr++ = '\n';
	write(1, buffer, length);
}