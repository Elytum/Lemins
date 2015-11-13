/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsavry <nsavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:03:32 by nsavry            #+#    #+#             */
/*   Updated: 2013/12/13 17:06:41 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strcpy(char *str1, const char *str2)
{
	int		i;

	i = 0;
	while (str2[i] != 0)
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = 0;
	return (str1);
}
