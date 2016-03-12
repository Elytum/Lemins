/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <vector.h>
#include <lemins.h>
#include <stdio.h>
#include <unistd.h>

static t_path		*generate_paths2(size_t total, t_path *paths)
{
	size_t			i;
	size_t			remain;
	size_t			extra;
	size_t			tmp;

	i = 0;
	while (paths[i].begin)
	{
		paths[i].ants = 0;
		++i;
	}
	extra = total;
	while (extra)
	{
		i = 0;
		remain = 0;
		total = extra;
		while (paths[i].begin && extra)
		{
			tmp = total / paths[i].len + remain;
			paths[i].ants += tmp;
			extra -= tmp;
			remain = total % paths[i++].len;
		}
		if (!extra)
			return (paths);
		paths[0].ants += remain;
		extra -= remain;
	}
	return (paths);
}

static t_path		*generate_paths(size_t ants_nb, t_map *map)
{
	size_t			total;
	size_t			i;
	t_vector		*ptr;
	t_path			*paths;

	if (!(paths = (t_path *)malloc(sizeof(t_path) * (map->solutions->len + 1))))
	{
		write(1, "Malloc error\n", 13);
		exit(0);
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
	return (generate_paths2(ants_nb, paths));
}

static void			solution_push_ants(size_t *id, t_path *paths, t_ant *ants)
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

static void			update_ants(size_t *ants_nb, size_t nb_ants, t_ant *ants)
{
	size_t			i;
	char			updated;

	i = 0;
	updated = 0;
	while (i < nb_ants)
	{
		if (ants[i].path)
		{
			(updated) ? write(1, " L", 2) : write(1, "L", 1);
			ft_putnbr(i + 1);
			write(1, "-", 1);
			write(1, *ants[i].path, ft_strlen(*ants[i].path));
			ants[i].path++;
			updated = 1;
			if (!*ants[i].path)
			{
				--*ants_nb;
				ants[i].path = NULL;
			}
		}
		++i;
	}
	write(1, "\n", 1);
}

void				tell_solutions(t_map *map)
{
	const size_t	save_nb = map->ants_nb;
	size_t			id;
	t_ant			*ants;
	t_path			*paths;

	if (map->direct == 1)
	{
		map->solution = new_vector(sizeof(char *));
		add_vector(map->solution, map->end);
		add_vector(map->solution, NULL);
		add_vector(map->solutions, map->solution);
	}
	if (!(paths = generate_paths((map->ants_nb), map)) ||
		!(ants = (t_ant *)ft_memalloc(sizeof(t_ant) * (map->ants_nb + 2))))
	{
		free(paths);
		write(1, "Malloc error\n", 13);
		exit(0);
	}
	id = 0;
	while ((map->ants_nb))
	{
		solution_push_ants(&id, paths, ants);
		update_ants(&(map->ants_nb), save_nb, ants);
	}
}
