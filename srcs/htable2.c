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

#include <htable.h>
#include <string.h>
#include <limits.h>
#include <libft.h>

void					ht_fln(t_entry *first, t_entry **next,
										t_entry **last, const char *key)
{
	*next = first;
	*last = NULL;
	while ((*next) != NULL && (*next)->key != NULL &&
			ft_strcmp(key, (*next)->key) > 0)
	{
		*last = (*next);
		(*next) = (*next)->next;
	}
}

void					ht_set(t_hashtable *hashtable, char *key, void *value)
{
	const int			bin = ht_hash(hashtable, key);
	t_entry				*newpair;
	t_entry				*next;
	t_entry				*last;

	ht_fln(hashtable->table[bin], &next, &last, key);
	if (next != NULL && next->key != NULL && ft_strcmp(key, next->key) == 0)
	{
		free(next->value);
		next->value = value;
	}
	else
	{
		newpair = ht_newpair(key, value);
		if (next == hashtable->table[bin])
		{
			newpair->next = next;
			hashtable->table[bin] = newpair;
			return ;
		}
		last->next = newpair;
		if (next)
			newpair->next = next;
	}
}

void					*ht_get(t_hashtable *hashtable, char *key)
{
	int					bin;
	t_entry				*pair;

	bin = ht_hash(hashtable, key);
	pair = hashtable->table[bin];
	while (pair != NULL && pair->key != NULL && ft_strcmp(key, pair->key) > 0)
		pair = pair->next;
	if (pair == NULL || pair->key == NULL || ft_strcmp(key, pair->key) != 0)
		return (NULL);
	else
		return (pair->value);
}

t_entry					*ht_get_pair(t_hashtable *hashtable, char *key)
{
	int					bin;
	t_entry				*pair;

	bin = ht_hash(hashtable, key);
	pair = hashtable->table[bin];
	while (pair != NULL && pair->key != NULL && ft_strcmp(key, pair->key) > 0)
		pair = pair->next;
	if (pair == NULL || pair->key == NULL || ft_strcmp(key, pair->key) != 0)
		return (NULL);
	else
		return (pair);
}

void					ht_remove(t_hashtable *hashtable, char *key)
{
	int					bin;
	t_entry				*pair;
	t_entry				*old;

	bin = ht_hash(hashtable, key);
	pair = hashtable->table[bin];
	old = NULL;
	while (pair != NULL && pair->key != NULL && ft_strcmp(key, pair->key) > 0)
	{
		old = pair;
		pair = pair->next;
	}
	if (pair == NULL || pair->key == NULL || ft_strcmp(key, pair->key) != 0)
		return ;
	else
	{
		if (old)
			old->next = pair->next;
		free(pair->key);
		free(pair->value);
		free(pair);
		if (!old)
			hashtable->table[bin] = NULL;
	}
}
