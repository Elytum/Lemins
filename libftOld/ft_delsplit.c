/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <smarie-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:38:33 by smarie-c          #+#    #+#             */
/*   Updated: 2014/02/14 18:43:11 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_delsplit(char ***split)
{
	int		i;

	if (split && *split)
	{
		i = 0;
		while ((*split)[i])
		{
			ft_strdel(&((*split)[i]));
			i++;
		}
		free(*split);
		*split = NULL;
	}
}
