/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>
#include <htable.h>
#include <stdio.h>
#include <libft.h>
#include <fcntl.h>
#include <string.h>
#include <lemins.h>

static void		remove_used(t_map *map)
{
	size_t		i;
	void		*tmp;

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

static void		solve_master(t_map *map)
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
			break ;
		}
		remove_used(map);
		add_vector(map->solution, map->end);
		add_vector(map->solution, NULL);
		add_vector(map->solutions, map->solution);
	}
	if (map->solutions->len || map->direct)
		tell_solutions(map);
	else
		write(1, "Error 1\n", 8);
}

static int		extract_nb_ants(t_map *map)
{
	char		*line;
	char		*ptr;

	if (get_next_line(0, &line) != 1 || *line < '0' || *line > '9')
	{
		write(1, "Error 3\n", 8);
		return (0);
	}
	ptr = line;
	while (*ptr)
	{
		if (*ptr < '0' || *ptr > '9')
		{
			if (*ptr == '\n')
				break ;
			return (0);
		}
		++ptr;
	}
	map->ants_nb = ft_atoi(line);
	free(line);
	return (1);
}

int				main(void)
{
	char		*line;
	t_map		map;

	bzero(&map, sizeof(map));
	map.cells = ht_create(2048);
	map.list = new_vector(sizeof(char *));
	map.ants_nb = 3;
	if (!extract_nb_ants(&map))
		return (1);
	line = NULL;
	while (get_next_line(0, &line) == 1)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		if (!analyze_line(line, &map))
			break ;
		free(line);
	}
	write(1, "\n", 1);
	if (map.start && map.end)
		solve_master(&map);
	else
		write(1, "Error 0\n", 8);
	return (1);
}
