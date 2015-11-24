#include <lemins.h>
#include <unistd.h>

#include <stdio.h>

void		maze_message(t_maze * const maze, const char str[])
{
	if (maze->bonus.verbose == B_TRUE)
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
}

static void	maze_tell_position(const int x, const int y)
{
	write(1, "[", 1);
	ft_putnbr(x);
	write(1, "/", 1);
	ft_putnbr(y);
	write(1, "]", 1);
}

void		maze_cell(t_maze * const maze, const char name[], const int x, const int y)
{
	const char		intro[] = "Cell [";
	const char		announcer[] = "] is added in ";
	const char		outro[] = "\n";

	if (maze->bonus.verbose == B_TRUE)
	{
		write(1, intro, sizeof(intro) - 1);
		write(1, name, ft_strlen(name));
		write(1, announcer, sizeof(announcer) - 1);
		maze_tell_position(x, y);
		write(1, outro, sizeof(outro) - 1);
	}
}

void		maze_link(t_maze * const maze, const char first_cell[], char const second_cell[])
{
	const char		intro[] = "Cell [";
	const char		announcer[] = "] is linked with cell [";
	const char		outro[] = "]\n";

	if (maze->bonus.verbose == B_TRUE)
	{
		write(1, intro, sizeof(intro) - 1);
		write(1, first_cell, ft_strlen(first_cell));
		write(1, announcer, sizeof(announcer) - 1);
		write(1, second_cell, ft_strlen(second_cell));
		write(1, outro, sizeof(outro) - 1);
	}
}

void		maze_error(t_maze * const maze, const char str[])
{
	maze_error(maze, str);
	maze->keep_reading = B_FALSE;
}