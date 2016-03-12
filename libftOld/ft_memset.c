/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 22:59:41 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 05:59:12 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*chg;

	chg = b;
	i = 0;
	while (i < n)
	{
		chg[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
