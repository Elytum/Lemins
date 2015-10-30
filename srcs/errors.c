#include <lemins.h>

void		maze_error(t_maze * const maze, const char str[])
{
	if (maze->verbose)
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	maze->keep_reading = B_FALSE;
}
