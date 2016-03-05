#include <vector.h>
#include <htable.h>
#include <stdio.h>
#include <libft.h>
#include <get_next_line.h>
#include <fcntl.h>
#include <string.h>

typedef struct		s_map
{
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

int		check_comment(char *line, char *flag)
{
	if (line[0] == '#')
	{
		if (!strcmp(line + 1, "start"))
		{
			if (*flag & HAVE_START)
				return (0);
			*flag |= IS_START;
		}
		else if (!strcmp(line + 1, "end"))
		{
			if (*flag & HAVE_END)
				return (0);
			*flag |= IS_END;
		}
		else
			return (0);
	}
	return (1);
}

int			get_names(char *line, char *linked[2])
{
	char	*delimiter;

	delimiter = strchr(line, '-');
	if (!delimiter)
		return (0);
	*delimiter = '\0';
	linked[0] = line;
	linked[1] = delimiter + 1;
	return (1);
}

int		check_link(char *line, t_map *map)
{
	char	*linked[2];
	entry_t *pairs[2];

	if (!get_names(line, linked))
		return (0);
	if (!(pairs[0] = ht_get_pair(map->cells, linked[0])) ||
		!(pairs[1] = ht_get_pair(map->cells, linked[1])))
		return (0);
	if (pairs[0]->key == pairs[1]->key)
		return (1);
	if ((pairs[0]->key == map->start || pairs[0]->key == map->end) &&
		(pairs[1]->key == map->start || pairs[1]->key == map->end))
	{
		map->direct = 1;
		return (1);
	}
	add_vector(pairs[0]->value, pairs[1]->key);
	add_vector(pairs[1]->value, pairs[0]->key);
	return (1);
}

void		*ft_memdup(const char *src, size_t len)
{
	char	*buffer;

	if (!(buffer = malloc(sizeof(char) * (len))))
		return (NULL);
	memcpy(buffer, src, len);
	buffer[len] = '\0';
	return (buffer);
}

void		*get_name(char *line)
{
	char	*ptr;
	char	loop;

	loop = 2;
	if ((ptr = line + strlen(line) - 1) <= line)
		return (NULL);
	while (ptr > line && (*ptr == ' ' || *ptr == '\t'))
		--ptr;
	while (loop--)
	{
		if (!(*ptr >= '0' && *ptr <= '9'))
			return (NULL);
		while (ptr > line && (*ptr >= '0' && *ptr <= '9'))
			--ptr;
		if (*ptr == '+' || *ptr == '-')
			--ptr;
		if (ptr == line || (*ptr != ' ' && *ptr != '\t'))
			return (NULL);
		while (ptr > line && (*ptr == ' ' || *ptr == '\t'))
			--ptr;
	}
	return (ft_memdup(line, ptr - line + 1));
}

int		check_cell(char *line, char *flag, t_map *map)
{
	char	*name;

	if (!(name = get_name(line)))
		return (0);
	if (ht_get(map->cells, name))
		return (0);
	if (*flag & IS_START)
	{
		map->start = name;
		*flag &= ~IS_START;
		*flag |= HAVE_START;
	}
	else if (*flag & IS_END)
	{
		map->end = name;
		*flag &= ~IS_END;
		*flag |= HAVE_END;
	}
	ht_set(map->cells, name, new_vector(sizeof(char *)));
	add_vector(map->list, name);
	++map->size;
	return (1);
}

char	analyze_line(char *line, t_map *map)
{
	static char flag = 0;

	if (line[0] == '#')
		return (check_comment(line + 1, &flag));
	else if (flag & CELLS_DONE)
		return (check_link(line, map));
	else if (!check_cell(line, &flag, map))
	{
		flag |= CELLS_DONE;
		return (check_link(line, map));
	}
	return (1);
}

void	save_solution(t_map *map)
{
	size_t	i;
	char	*tmp;

	i = 0;
	map->len = map->working_list->len;
	map->solution->len = 0;
	while (i < map->working_list->len)
	{
		if ((tmp = get_vector(*(map->working_list), i)))
			add_vector(map->solution, tmp);
		++i;
	}
}

int		solve(t_map *map, char *cell, size_t level);

	//Iterate though unknown cells
void	solve_iterate(t_map *map, t_vector *vector, size_t level)
{
	size_t	i;
	void	*tmp;
	size_t	tmp_pos;

	i = 0;
	tmp_pos = add_vector(map->working_list, NULL);
	while (i < vector->len)
	{
		tmp = get_vector(*vector, i);
		if (in_vector(*(map->list), tmp) &&
			!in_vector(*(map->working_list), tmp))
		{
			set_vector(map->working_list, tmp, tmp_pos);
			if (solve(map, tmp, level + 1))
				break ;
		}
		++i;
	}
	--map->working_list->len;
}

	//Look for END cell
int		solve(t_map *map, char *cell, size_t level)
{
	t_vector	*vector;
	size_t		i;

	if (level >= map->len)
		return (1);
	vector = ht_get(map->cells, cell);
	if (!vector->len)
		return (0);
	i = 0;
	while (i < vector->len)
	{
		if (get_vector(*vector, i) == map->end)
		{
			save_solution(map);
			return (1);
		}
		++i;
	}
	solve_iterate(map, vector, level);
	return (0);
}

void	tell_solution(t_map *map)
{
	size_t	i;

	printf("Solution: (%zu)\n", map->solution->len);
	i = 0;
	while (i < map->solution->len)
		printf("\t%s\n", (char *)get_vector(*(map->solution), i++));
}

t_path			*generate_paths(size_t ants_nb, t_map *map)
{
	size_t		total;
	size_t		i;
	size_t		remain;
	t_vector	*ptr;
	t_path		*paths;

	if (!(paths = (t_path *)malloc(sizeof(t_path) * map->solutions->len + 1)))
	{
		printf("Error\n");
		return (paths);
	}
	total = 0;
	i = 0;
	while (i < map->solutions->len)
	{
		ptr = (t_vector *)get_vector(*map->solutions, i);
		paths[i].begin = (char **)get_vector_addr(*ptr, 0);
		paths[i].len = ptr->len;
		total += ptr->len;
		++i;
	}
	paths[i].begin = NULL;
	remain = 0;
	i = 0;
	total *= ants_nb;
	while (paths[i].begin)
	{
		paths[i].ants = total / paths[i].len + remain;
		remain += total % paths[i].len;
		++i;
	}
	paths[0].ants += remain;
	return (paths);
}

void	solution_push_ants(size_t *id, t_path *paths, t_ant *ants)
{
	size_t			i;

	i = 0;
	while (paths[i].begin)
	{
		if (paths[i].ants)
		{
			ants[*id].path = paths[i].begin;
			++(*id);
			--paths[i].ants;
		}
		++i;
	}
}

void	update_ants(size_t *ants_nb, size_t nb_ants, t_ant *ants)
{
	size_t	i;
	char	updated = 0;

	i = 0;
	while (i < nb_ants)
	{
		if (ants[i].path)
		{
			if (updated)
				printf(" L%zu-%s", i + 1, *ants[i].path++);
			else
				printf("L%zu-%s", i + 1, *ants[i].path++);
			updated = 1;
			if (!*ants[i].path)
			{
				--*ants_nb;
				ants[i].path = NULL;
			}
		}
		++i;
	}
	printf("\n");
	(void)ants_nb;
	(void)ants;
}

void	tell_solutions(t_map *map)
{
	size_t			ants_nb = 3;
	const size_t	save_nb = ants_nb;
	size_t			id;
	t_ant			*ants;
	t_path			*paths;

	if (!(paths = generate_paths(ants_nb, map)))
	{
		printf("Error\n");
		return ;
	}
	if (!(ants = (t_ant *)ft_memalloc(sizeof(t_ant) * ants_nb)))
	{
		free(paths);
		printf("Error\n");
		return ;
	}
	id = 0;
	while (ants_nb)
	{
		solution_push_ants(&id, paths, ants);
		update_ants(&ants_nb, save_nb, ants);
	}
}

void	remove_used(t_map *map)
{
	size_t	i;
	void	*tmp;

	tmp = map->working_list;
	map->working_list = map->list;
	map->list = tmp;
	map->list->len = 0;
	i = 0;
	while (i < map->working_list->len)
	{
		tmp = get_vector(*(map->working_list), i);
		if (!in_vector(*(map->solution), tmp))
			add_vector(map->list, tmp);
		++i;
	}
}

void	solve_master(t_map *map)
{
	map->solutions = new_vector(sizeof(t_vector *));
	map->working_list = new_vector(sizeof(char *));
	while (42)
	{
		map->len = map->list->len;
		map->working_list->len = 0;
		map->solution = new_vector(sizeof(char *));
		solve(map, map->start, 1);
		if (map->solution->len == 0)
		{
			free_vector(map->solution);
			break;
		}
		add_vector(map->solution, map->end);
		add_vector(map->solution, NULL);
		add_vector(map->solutions, map->solution);
		remove_used(map);
	}
	if (map->solutions->len)
		tell_solutions(map);
}

int		main(void)
{
	int		fd;
	char	*line;
	t_map	map;

	line = NULL;
	map.cells = ht_create(2048);
	map.size = 0;
	map.list = new_vector(sizeof(char *));
	map.direct = 0;
	if ((fd = open("./sample/map2", O_RDONLY)) == -1)
		return (1);
	while (get_next_line(fd, &line) == 1)
	{
		line[strlen(line) - 1] = '\0';
		if (!analyze_line(line, &map))
			break ;
		free(line);
	}
	if (map.start && map.end)
		solve_master(&map);
	else
		printf("Missing start or end\n");
	return (1);
}
