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
}					t_map;

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
	printf("Name: [%s] %p\n", name, name);
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
	printf("\t->%p\n", ht_get_pair(map->cells, name)->key);
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

void	solve(t_map map)
{
	size_t		i;
	char		*cell;
	t_vector	*vector;

	cell = map.start;
	printf("Start: [%s], end: [%s]\n", map.start, map.end);
	vector = ht_get(map.cells, cell);
	i = 0;
	while (i < vector->len)
	{
		if (get_vector(*vector, i) == map.end)
			printf ("DONE\n");
		else
			printf ("Cell [%s]\n", (char *)get_vector(*vector, i));
		++i;
	}
	(void)map;
}

int		main(void)
{
	int		fd;
	char	*line;
	t_map	map;

	line = NULL;
	map.cells = ht_create(2048);
	if ((fd = open("./sample/map", 'r')) == -1)
		return (1);
	while (get_next_line(fd, &line) == 1)
	{
		line[strlen(line) - 1] = '\0';
		if (!analyze_line(line, &map))
			break ;
		free(line);
	}
	if (map.start && map.end)
		solve(map);
	else
		printf("Missing start or end\n");
	return (1);
}
