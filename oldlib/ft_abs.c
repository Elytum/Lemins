/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsavry <nsavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/13 12:47:06 by nsavry            #+#    #+#             */
/*   Updated: 2013/12/17 18:01:00 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_abs(int nb)
{
	if (nb == -2147483648)
		return (nb);
	else if (nb < 0)
		return (-nb);
	return (nb);
}
