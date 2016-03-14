/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:20:13 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 18:11:29 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>

typedef struct	s_vector
{
	void		*content;
	size_t		size;
	size_t		len;
	size_t		max;
}				t_vector;

t_vector		create_vector(size_t size);
t_vector		*new_vector(size_t size);
void			free_vector(t_vector *vector);
size_t			add_vector(t_vector *vector, void *data);
void			set_vector(t_vector *vector, void *data, size_t position);
void			*get_vector(t_vector vector, size_t position);
void			**get_vector_addr(t_vector vector, size_t position);
int				in_vector(t_vector vector, void *data);

#endif
