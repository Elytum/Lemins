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
	if (line[0] == '#')
	{
		if (!ft_strcmp(line + 1, "start"))
		{
			if (*flag & HAVE_START)
				return (0);
			*flag |= IS_START;
		}
		else if (!ft_strcmp(line + 1, "end"))
		{
			if (*flag & HAVE_END)
				return (0);
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

	if (!(delimiter = ft_strchr(line, '-')))
		return (0);
	*delimiter = '\0';
	linked[0] = line;
	linked[1] = delimiter + 1;
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

static int	check_cell(char *line, char *flag, t_map *map)
{
	char	*name;
	void	*ptr;

	if (!(name = get_name(line)) || ht_get(map->cells, name))
		return (0);
	if (*flag & IS_START && *flag & IS_END)
		exit(write(1, "Error\n", 6));
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
	if (!(ptr = new_vector(sizeof(char *))))
		exit(1);
	ht_set(map->cells, name, ptr);
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
