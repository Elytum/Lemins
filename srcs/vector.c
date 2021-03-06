/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>
#include <libft.h>

#include <stdio.h>

t_vector		create_vector(size_t size)
{
	t_vector	new_vector;

	new_vector.size = size;
	new_vector.len = 0;
	new_vector.content = NULL;
	return (new_vector);
}

t_vector		*new_vector(size_t size)
{
	t_vector	*new_vector;

	if (!(new_vector = (t_vector *)malloc(sizeof(t_vector))))
	{
		exit(0);
		return (NULL);
	}
	new_vector->size = size;
	new_vector->len = 0;
	new_vector->content = NULL;
	return (new_vector);
}

void			free_vector(t_vector *vector)
{
	if (vector->content)
	{
		free(vector->content);
		vector->content = NULL;
	}
}

size_t			add_vector(t_vector *vector, void *data)
{
	void		*tmp;

	if (!vector->content)
	{
		vector->len = 0;
		vector->max = 1;
		if (!(vector->content = (void *)malloc(vector->max * vector->size)))
			exit(0);
	}
	else if (vector->len == vector->max)
	{
		tmp = vector->content;
		if (!(vector->content = (void *)malloc(vector->max * 2 * vector->size)))
			exit(0);
		ft_memcpy(vector->content, tmp, vector->max * vector->size);
		free(tmp);
		vector->max *= 2;
	}
	ft_memcpy(vector->content + vector->size * vector->len,
				&data, vector->size);
	return (vector->len++);
}

void			set_vector(t_vector *vector, void *data, size_t position)
{
	if (position > vector->len)
		return ;
	ft_memcpy(vector->content + vector->size * position,
				&data, vector->size);
}
