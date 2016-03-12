/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 04:03:09 by smarie-c          #+#    #+#             */
/*   Updated: 2013/11/27 17:54:22 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	size_t	i;
	size_t	j;

	i = ft_strlen(s);
	new = ft_strnew(i + 1);
	j = 0;
	while (s[j] != '\0')
	{
		new[j] = f(s[j]);
		j++;
	}
	return (new);
}
