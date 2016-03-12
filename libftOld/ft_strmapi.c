/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 04:13:02 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 06:01:04 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	size_t			i;
	unsigned int	j;

	i = ft_strlen(s);
	new = ft_strnew(i + 1);
	j = 0;
	while (s[j] != '\0')
	{
		new[j] = f(j, s[j]);
		j++;
	}
	return (new);
}
