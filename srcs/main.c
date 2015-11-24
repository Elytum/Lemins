#include <stdio.h>

#include <lemins.h>
#include <libft.h>

#include <fcntl.h>

static t_maze	*init_maze(const char * const path)
{
	t_maze	*maze;
	int		fd;

	if ((fd = open(path, O_RDONLY)) <= 0)
		return (NULL);
	if (!(maze = (t_maze *)malloc(sizeof(t_maze))))
		return (NULL);
	maze->analysing = CELLS;
	maze->fd = fd;
	maze->keep_reading = B_TRUE;
	maze->cells = ht_create( 65536 );
	maze->cell_kind = NORMAL;
	maze->start = NULL;
	maze->end = NULL;
	// maze->verbose = B_FALSE;
	maze->verbose = B_TRUE;
	return (maze);
}

int main(const int ac, const char * const * const av)
{
	char	*str;
	t_maze	*maze;

	if (ac != 2 || !(maze = init_maze(av[1])))
		return (ERROR_EXIT);
	while (DO_READ(maze) && get_next_line(maze->fd, &str) == 1)
	{
		extract_data(maze, str);
		if (DO_ANALYSE(maze))
			analyse_data(maze);
		free(str);
	}
	return (NORMAL_EXIT);
}