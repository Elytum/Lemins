/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 23:03:11 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 05:58:24 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t			i;
	char			*dst;
	const char		*src;

	i = 0;
	dst = s1;
	src = s2;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
