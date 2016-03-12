/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <htable.h>
#include <lemins.h>
#include <vector.h>
#include <stdio.h>

static void	*get_name(char *line)
{
	char	*ptr;
	char	loop;

	if (*line == 'L')
		return (NULL);
	loop = 2;
	if ((ptr = line + ft_strlen(line) - 1) <= line)
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

static int	check_comment(char *line, char *flag)
{
	// printf("Check comment\n");
	if (line[0] == '#')
	{
		if (!ft_strcmp(line + 1, "start"))
		{
			if (*flag & HAVE_START)
			{
				printf("Test 1\n");
				return (0);
			}
			*flag |= IS_START;
		}
		else if (!ft_strcmp(line + 1, "end"))
		{
			if (*flag & HAVE_END)
			{
				printf("Test 2\n");
				return (0);
			}
			*flag |= IS_END;
		}
	}
	return (1);
}

static int	check_link(char *line, t_map *map)
{
	char	*linked[2];
	entry_t	*pairs[2];
	char	*delimiter;

	// printf("Check link\n");
	if (!(delimiter = ft_strchr(line, '-')))
	{
		printf("Test 0\n");
		return (0);
	}
	*delimiter = '\0';
	linked[0] = line;
	linked[1] = delimiter + 1;
	if (!(pairs[0] = ht_get_pair(map->cells, linked[0])) ||
		!(pairs[1] = ht_get_pair(map->cells, linked[1])))
	{
		printf("Test [%s] [%s]\n", linked[0], linked[1]);
		printf("%p %p\n", pairs[0], pairs[1]);
		return (0);
	}
	if (pairs[0]->key == pairs[1]->key)
	{
		printf("Test 3\n");
		return (1);
	}
	if ((pairs[0]->key == map->start || pairs[0]->key == map->end) &&
		(pairs[1]->key == map->start || pairs[1]->key == map->end))
	{
		map->direct = 1;
		printf("Test 1\n");
		return (1);
	}
	add_vector(pairs[0]->value, pairs[1]->key);
	add_vector(pairs[1]->value, pairs[0]->key);
	// printf("Ok\n");
	return (1);
}

static int	check_cell(char *line, char *flag, t_map *map)
{
	char	*name;

	// printf("Check cell\n");
	if (!(name = get_name(line)) || ht_get(map->cells, name))
		return (0);
	if (*flag & IS_START && *flag & IS_END)
	{
		write(1, "\nError 2\n", 9);
		exit(1);
	}
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

char		analyze_line(char *line, t_map *map)
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
