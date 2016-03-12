/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 18:08:08 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 05:57:03 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*ft_fill_min(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static char		*ft_fill_number(int nbr, int size, char *str, int i)
{
	int			tmp;

	tmp = nbr;
	size = 1;
	while (tmp / 10 > 0)
	{
		size *= 10;
		tmp /= 10;
	}
	while (size > 0)
	{
		tmp = 0;
		tmp = nbr / size;
		nbr %= size;
		size = size / 10;
		str[i] = '0' + tmp;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_itoa(int nbr)
{
	int			size;
	int			i;
	char		*str;

	size = 1;
	str = (char*)malloc(13);
	i = 0;
	if (nbr == -2147483648)
		return (ft_fill_min(str));
	if (nbr < 0)
	{
		str[i] = '-';
		nbr = nbr * -1;
		i++;
	}
	str = ft_fill_number(nbr, size, str, i);
	return (str);
}
