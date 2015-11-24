#include <lemins.h>

u_double_int	no_error(void)
{
	u_double_int	error;

	error.value = 0;
	return (error);
}

u_double_int	error(enum error, int fragments)
{
	u_double_int	error;

	error.array[0] = error;
	error.array[1] = fragments;
	return (error);
}
