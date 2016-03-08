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

int		check_comment(char *line, char *flag)
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
		else
			return (0);
	}
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
