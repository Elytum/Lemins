/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 23:06:57 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 05:57:39 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*buffdest;
	const char	*buffsrc = src;
	size_t		i;

	buffdest = dest;
	i = 0;
	while (n != 0)
	{
		buffdest[i] = buffsrc[i];
		if (buffdest[i] == c)
		{
			i++;
			return (buffdest + i);
		}
		buffdest[i] = buffsrc[i];
		i++;
		n--;
	}
	return (NULL);
}
