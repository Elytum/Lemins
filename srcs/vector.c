#include <vector.h>
#include <libft.h>

#include <stdio.h>

t_vector		create_vector(size_t size)
{
	t_vector	new_vector;

	new_vector.size = size;
	new_vector.content = NULL;
	return (new_vector);
}

t_vector		*new_vector(size_t size)
{
	t_vector	*new_vector;

	if (!(new_vector = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	new_vector->size = size;
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

void			add_vector(t_vector *vector, void *data)
{
	void		*tmp;

	if (!vector->content)
	{
		vector->len = 0;
		vector->max = 1;
		vector->content = (void *)malloc(vector->max * vector->size);
	}
	else if (vector->len == vector->max)
	{
		tmp = vector->content;
		vector->content = (void *)malloc(vector->max * 2 * vector->size);
		ft_memcpy(vector->content, tmp, vector->max * vector->size);
		free(tmp);
		vector->max *= 2;
	}
	ft_memcpy(vector->content + vector->size * vector->len,
				&data, vector->size);
	++vector->len;
}

void			*get_vector(t_vector vector, size_t position)
{
	void		**tmp;

	if (position > vector.len)
		return (NULL);
	tmp = vector.content + vector.size * position;
	return (*tmp);
	// return (vector.content + vector.size * position);
}