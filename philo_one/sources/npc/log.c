/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 22:17:38 by ahallain          #+#    #+#             */
/*   Updated: 2021/04/05 01:53:07 by ahallain         ###   ########.fr       */
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

void	console_log(size_t millis, size_t id, char *str)
{
	size_t			length;
	char			*buffer;
	char			*ptr;

	length = 3 + ft_strlen(str) + nbrlen(millis) + nbrlen(id);
	if (!(buffer = malloc(sizeof(char) * length)))
		return ;
	ptr = buffer;
	fill_nbr(&ptr, millis);
	*ptr++ = '\t';
	fill_nbr(&ptr, id);
	*ptr++ = ' ';
	fill_str(&ptr, str);
	*ptr++ = '\n';
	write(1, buffer, length);
	free(buffer);
}
