#ifndef LEMINS_H
# define LEMINS_H

#include <vector.h>
#include <htable.h>

typedef struct		s_map
{
	size_t			ants_nb;
	char			*start;
	char			*end;
	hashtable_t		*cells;
	size_t			size;
	t_vector		*list;
	t_vector		*working_list;
	t_vector		*solution;
	t_vector		*solutions;
	size_t			len;
	int				direct;
}					t_map;

typedef struct	s_ant
{
	char		**path;
}				t_ant;

typedef struct	s_path
{
	char		**begin;
	size_t		len;
	size_t		ants;
}				t_path;

#define MAX(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

#define IS_START    0b10000000
#define IS_END      0b01000000
#define HAVE_START  0b00100000
#define HAVE_END    0b00010000
#define CELLS_DONE  0b00001000

int			get_names(char *line, char *linked[2]);
void		*get_name(char *line);
char		analyze_line(char *line, t_map *map);

void		save_solution(t_map *map);
void		solve_iterate(t_map *map, t_vector *vector, size_t level);
int			solve(t_map *map, char *cell, size_t level);
void		tell_solution(t_map *map);
void		tell_solutions(t_map *map);
void		error(const char *str);

#endif
