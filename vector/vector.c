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
		printf("Allocating %lu\n", vector->max * vector->size);
		vector->content = (void *)malloc(vector->max * vector->size);
	}
	else if (vector->len == vector->max)
	{
		tmp = vector->content;
		vector->content = (void *)malloc(vector->max * 2 * vector->size);
		ft_memcpy(vector->content, tmp, vector->max * vector->size);
		vector->max *= 2;
	}
	printf("Position: [%lu]\n", vector->size * vector->len);
	printf("Size: [%lu]\n", vector->size);
	ft_memcpy(vector->content + vector->size * vector->len,
				data, vector->size);
	++vector->len;
}

void			*get_vector(t_vector vector, size_t position)
{
	if (position > vector.len)
		return (NULL);
	return (vector.content + vector.size * vector.len);
}