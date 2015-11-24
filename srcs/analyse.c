#include <lemins.h>

#include <stdio.h>


static void		tell_cell(t_maze * const maze, const char * const name)
{
	u_double_int	double_int;

	if (!(double_int.total = ht_get(maze->cells, name)))
		maze_error(maze, "Cell adding failed !");
	else
		maze_cell(maze, name, double_int.array[0], double_int.array[1]);
}

static void		add_cell(t_maze * const maze)
{
	u_double_int	double_int;

	double_int.array[0] = maze->pos_x;
	double_int.array[1] = maze->pos_y;
	ht_set(maze->cells, strdup(maze->first_cell), double_int.total);
}

static void		analyze_cell(t_maze * const maze)
{
	if (maze->cell_kind == START)
	{
		if (!maze->start)
		{
			maze->start = ft_strdup(maze->first_cell);
			maze->cell_kind = NORMAL;
		}
		else
			maze_error(maze, "Repeated start !");
	}
	else if (maze->cell_kind == END)
	{
		if (!maze->end)
		{
			maze->end = ft_strdup(maze->first_cell);
			maze->cell_kind = NORMAL;
		}
		else
			maze_error(maze, "Repeated end !");
	}
	add_cell(maze);
	tell_cell(maze, maze->first_cell);
}

static void		analyze_link(t_maze * const maze)
{
	if (maze->cell_kind != NORMAL)
		maze_error(maze, "Link while it should be a cell !");
	else
		maze_link(maze, maze->first_cell, maze->second_cell);
}

void			analyse_data(t_maze * const maze)
{
	if (IS_CELL(maze))
		analyze_cell(maze);
	else
		analyze_link(maze);
}
