/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 23:14:49 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 05:58:09 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*buff1;
	const unsigned char		*buff2;

	buff1 = s1;
	buff2 = s2;
	i = 0;
	while (i < n && buff1[i] == buff2[i])
		i++;
	if (i == n)
		return (0);
	return (buff1[i] - buff2[i]);
}
