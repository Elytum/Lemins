#include <vector.h>
#include <string.h>

#include <stdio.h>

int		main(void)
{
	t_vector	vector;

	vector = create_vector(sizeof(int));

	add_vector(&vector, (void *)1);

	// add_vector(&vector, (void *)2);
	// add_vector(&vector, (void *)3);
	// add_vector(&vector, (void *)4);
	// add_vector(&vector, (void *)5);
	
	// printf("%i\n", (int)get_vector(vector, 3));
	return (0);
}