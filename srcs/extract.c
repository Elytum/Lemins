#include <lemins.h>
#include <htable.h>

static int		clear_line(const char *str)
{
	while (*str == ' ' && *str == '\t')
		++str;
	return (*str == '\0');
}

static void		extract_link(t_maze * const maze, char *str)
{
	*str++ = '\0';
	if (*str == 'L')
	{
		maze->keep_reading = B_FALSE;
		return ;
	}
	while (*str == ' ' || *str == '\t')
		++str;
	maze->second_cell = (void *)str;
	while (*str && *str != ' ' && *str != '\t' && *str != '#')
		++str;
	if (*str == '\0')
	{
		maze->analyse = B_TRUE;
		return ;
	}
	*str = '\0';
	while (*str == ' ' || *str == '\t')
		++str;
	if (*str)
		maze->keep_reading = B_FALSE;
	else
		maze->analyse = B_TRUE;
}

static void		extract_cell(t_maze * const maze, char *str)
{
	*str++ = '\0';
	while (*str == ' ' || *str == '\t')
		++str;
	maze->pos_x = ft_atoi(str);
	if (*str == '-' || *str == '+')
		++str;
	if (!(*str >= '0' && *str <= '9'))
	{
		maze_error(maze, "First value of the cell is not a number");
		return ;
	}
	while (*str >= '0' && *str <= '9')
		++str;
	while (*str == ' ' || *str == '\t')
		++str;
	maze->pos_y = ft_atoi(str);
	if (*str == '-' || *str == '+')
		++str;
	if (!(*str >= '0' && *str <= '9'))
	{
		maze_error(maze, "Second value of the cell is not a number");
		return ;
	}
	while (*str >= '0' && *str <= '9')
		++str;
	if (*str && *str != ' ' && *str != '\t')
	{
		maze_error(maze, "Second value of the cell is not a number");
		return ;
	}
	while (*str == ' ' || *str == '\t')
		++str;
	if (*str && !(maze->bonus.same_line_comments == B_TRUE && *str == '#'))
		maze_error(maze, "Line is not closed");
	else
	{
		maze->analyse = B_TRUE;
		maze->second_cell = NULL;
	}
}

static void	extract_command(t_maze * const maze, const char *str)
{
	if (maze->cell_kind != NORMAL)
	{
		maze_error(maze, "Command while it should be a cell !");
		return ;
	}
	if (str[0] == 's')
	{
		if (str[1] == 't' && str[2] == 'a' && str[3] == 'r' && str[4] == 't')
		{
			if (clear_line(str + sizeof("start") - 1))
				maze->cell_kind = START;
		}
	}
	else if (str[0] == 'e')
	{
		if (str[1] == 'n' && str[2] == 'd')
		{
			if (clear_line(str + sizeof("end") - 1))
				maze->cell_kind = END;
		}
	}
}

u_double_int	extract_data(t_maze * const maze, char *str)
{
	maze->analyse = B_FALSE;
	if (str[0] == '#' && str[1] == '#')
	{
		extract_command(maze, str + 2);
		return (no_error());
	}
	while (*str == ' ' || *str == '\t')
		++str;
	if (*str == '#')
		return (no_error());
	if (*str == 'L')
	{
		maze->keep_reading = B_FALSE;
		return (no_error());
	}
	maze->first_cell = (void *)str;
	while (*str && *str != ' ' && *str != '\t' && *str != '-' && *str != '#')
		++str;
	if (!*str || *str == '#')
		return (no_error());
	if (maze->analysing == CELLS)
	{
		if (*str == '-')
		{
			maze->analysing = LINKS;
			extract_link(maze, str);
		}
		else
			extract_cell(maze, str);
	}
	else
	{
		if (*str != '-')
			maze->analyse = B_FALSE;
		else
			extract_link(maze, str);
	}
	return (no_error());
}
