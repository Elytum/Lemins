/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 23:33:08 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 06:00:44 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	tot;
	int		i;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = 0;
	tot = lensrc + lendst;
	if (size >= lendst)
	{
		while (lendst < (size - 1))
		{
			dst[lendst] = src[i];
			lendst++;
			i++;
		}
		dst[lendst] = '\0';
		return (tot);
	}
	return (size + lensrc);
}
