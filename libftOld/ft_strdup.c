/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 14:56:27 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/27 14:24:57 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
		j++;
	copy = (char *)malloc(sizeof(char) * (j + 1));
	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
