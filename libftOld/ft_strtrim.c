/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 10:36:34 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 17:54:41 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	size_t		i;
	size_t		j;
	char		*new;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j && ((ft_isspace(s[i]) && !ft_oddprev(s, i - 1, '\\'))
					|| (s[i] == '\\' && s[i + 1] == '\n')
					|| (s[i] == '\n' && ft_oddprev(s, i - 1, '\\'))))
		i++;
	while (j >= i && ((ft_isspace(s[j]) && !ft_oddprev(s, j - 1, '\\'))
					|| (s[j] == '\\' && s[j + 1] == '\n')
					|| (s[j] == '\n' && ft_oddprev(s, j - 1, '\\'))))
		j--;
	if (j < i)
		j = i - 1;
	new = ft_strsub(s, i, j - i + 1);
	return (new);
}
