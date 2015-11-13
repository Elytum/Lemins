#include <vector.h>
#include <libft.h>

t_vector		create_vector(size_t size)
{
	t_vector	new_vector;

	new_vector.size = size;
	new_vector.content = NULL;
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
		vector->content = (void *)malloc(vector->max);
	}
	else if (vector->len == vector->max)
	{
		tmp = vector->content;
		vector->content = (void *)malloc(vector->max * 2);
		ft_memcpy(vector->content, tmp, vector->max * vector->size);
		vector->max *= 2;
	}
	ft_memcpy(vector->content + vector->size * vector->len,
				data, vector->size);
	++vector->len;
}