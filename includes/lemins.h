#ifndef LEMINS_H
# define LEMINS_H

#include <htable.h>
#include <libft.h>

#define ERROR_EXIT 1
#define NORMAL_EXIT 0

typedef union		s_double_int {
	void			*total;
	int				array[2];
}					u_double_int;

typedef enum		s_bool {
	B_FALSE = 0,
	B_TRUE = 1
}					e_bool;

typedef enum		s_cell_kind {
	NORMAL = 0,
	START,
	END
}					e_cell_kind;

typedef struct		s_maze
{
	int				fd;

	hashtable_t		*cells;

	char			*start;
	char			*end;

	e_bool			keep_reading;
	e_bool			analyse;
	e_cell_kind		cell_kind;

	void			*first_cell;
	void			*second_cell;
	int				pos_x;
	int				pos_y;

	e_bool			verbose;
}					t_maze;

#define DO_READ(maze) (maze->keep_reading == B_TRUE)
#define DO_ANALYSE(maze) (maze->analyse == B_TRUE)
#define IS_CELL(maze) (maze->second_cell == NULL)
#define IS_LINK(maze) (maze->second_cell != NULL)

void		extract_data(t_maze * const maze, char *str);
void		analyse_data(t_maze * const maze);
void		maze_error(t_maze * const maze, const char str[]);

#endif
