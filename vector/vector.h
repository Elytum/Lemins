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

#endif
