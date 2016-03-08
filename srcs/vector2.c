/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

void			*get_vector(t_vector vector, size_t position)
{
	void		**tmp;

	if (position > vector.len)
		return (NULL);
	tmp = vector.content + vector.size * position;
	return (*tmp);
}

void			**get_vector_addr(t_vector vector, size_t position)
{
	if (position > vector.len)
		return (NULL);
	return (vector.content + vector.size * position);
}

int				in_vector(t_vector vector, void *data)
{
	size_t		i;
	void		**tmp;

	i = 0;
	while (i < vector.len)
	{
		tmp = vector.content + vector.size * i;
		if (*tmp == data)
			return (1);
		++i;
	}
	return (0);
}
