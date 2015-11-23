#ifndef VECTOR_H
# define VECTOR_H

#include <stdlib.h>

typedef struct 	s_vector
{
	size_t		size;
	void		*content;
	size_t		len;
	size_t		max;
}				t_vector;

t_vector		create_vector(size_t size);
void			free_vector(t_vector *vector);
void			add_vector(t_vector *vector, void *data);
void			*get_vector(t_vector vector, size_t position);

#endif
