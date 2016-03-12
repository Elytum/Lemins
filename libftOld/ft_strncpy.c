/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 23:26:37 by smarie-c          #+#    #+#             */
/*   Updated: 2013/12/01 22:42:34 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	char	*dest;

	dest = s1;
	while (*s2 != '\0' && n > 0)
	{
		*dest = *s2;
		dest++;
		s2++;
		n--;
	}
	while (n > 0)
	{
		*dest = '\0';
		n--;
	}
	return (s1);
}