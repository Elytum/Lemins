/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 23:10:50 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 05:58:49 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*buff;

	buff = (unsigned char *)ft_memalloc(sizeof(unsigned char) * n);
	if (buff == NULL)
		return (NULL);
	ft_memcpy(buff, s2, n);
	ft_memcpy(s1, buff, n);
	free(buff);
	return (s1);
}
