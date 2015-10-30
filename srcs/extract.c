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
	if (!(*str >= '0' && *str <= '9'))
	{
		maze->keep_reading = B_FALSE;
		return ;
	}
	maze->pos_x = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		++str;
	while (*str == ' ' || *str == '\t')
		++str;
	if (!(*str >= '0' && *str <= '9'))
	{
		maze->keep_reading = B_FALSE;
		return ;
	}
	maze->pos_y = ft_atoi(str);
	maze->analyse = B_TRUE;
	maze->second_cell = NULL;
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

void	extract_data(t_maze * const maze, char *str)
{
	maze->analyse = B_FALSE;
	if (str[0] == '#' && str[1] == '#')
	{
		extract_command(maze, str + 2);
		return ;
	}
	while (*str == ' ' || *str == '\t')
		++str;
	if (*str == '#')
		return ;
	if (*str == 'L')
	{
		maze->keep_reading = B_FALSE;
		return ;
	}
	maze->first_cell = (void *)str;
	while (*str && *str != ' ' && *str != '\t' && *str != '-' && *str != '#')
		++str;
	if (!*str || *str == '#')
		return ;
	if (*str == '-')
		extract_link(maze, str);
	else
		extract_cell(maze, str);
}
