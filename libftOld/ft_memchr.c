/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 23:12:45 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 05:57:55 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*buff1;

	buff1 = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (*buff1 == (unsigned char)c)
			return ((void*)buff1);
		buff1++;
		i++;
	}
	return (NULL);
}
