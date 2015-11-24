#ifndef LEMINS_H
# define LEMINS_H

#include <htable.h>
#include <libft.h>

#define ERROR_EXIT 1
#define NORMAL_EXIT 0

typedef union		s_double_int {
	void			*total;
	int				array[2];
	double			value;
}					u_double_int;

typedef enum		s_bool {
	B_FALSE = 0,
	B_TRUE
}					e_bool;

typedef enum		s_analyse {
	CELLS = 0,
	LINKS
}					e_analyse;

typedef enum		s_cell_kind {
	NORMAL = 0,
	START,
	END
}					e_cell_kind;

typedef struct		s_bonus
{
	e_bool			verbose;
	e_bool			same_line_comments;
}					t_bonus;

typedef struct		s_maze
{
	e_analyse		analysing;
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

	t_bonus			bonus;
}					t_maze;

#define DO_READ(maze) (maze->keep_reading == B_TRUE)
#define DO_ANALYSE(maze) (maze->analyse == B_TRUE)
#define IS_CELL(maze) (maze->second_cell == NULL)
#define IS_LINK(maze) (maze->second_cell != NULL)

u_double_int		extract_data(t_maze * const maze, char *str);
void				analyse_data(t_maze * const maze);

typedef enum		s_error {
	B_FALSE = 0,
	B_TRUE
}					e_error;

u_double_int	error(enum error, int fragments);
u_double_int	no_error(void);

void		maze_message(t_maze * const maze, const char str[]);
void		maze_cell(t_maze * const maze, const char name[], const int x, const int y);
void		maze_link(t_maze * const maze, const char first_cell[], const char second_cell[]);
void		maze_error(t_maze * const maze, const char str[]);
#endif
