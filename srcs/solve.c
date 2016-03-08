/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemins.h>
#include <htable.h>
#include <stdio.h>

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
