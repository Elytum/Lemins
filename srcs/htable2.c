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

void					ht_fln(entry_t *first, entry_t **next,
										entry_t **last, const char *key)
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

void					ht_set(hashtable_t *hashtable, char *key, void *value)
{
	const int			bin = ht_hash(hashtable, key);
	entry_t				*newpair;
	entry_t				*next;
	entry_t				*last;

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

void					*ht_get(hashtable_t *hashtable, char *key)
{
	int					bin;
	entry_t				*pair;

	bin = ht_hash(hashtable, key);
	pair = hashtable->table[bin];
	while (pair != NULL && pair->key != NULL && ft_strcmp(key, pair->key) > 0)
		pair = pair->next;
	if (pair == NULL || pair->key == NULL || ft_strcmp(key, pair->key) != 0)
		return (NULL);
	else
		return (pair->value);
}

entry_t					*ht_get_pair(hashtable_t *hashtable, char *key)
{
	int					bin;
	entry_t				*pair;

	bin = ht_hash(hashtable, key);
	pair = hashtable->table[bin];
	while (pair != NULL && pair->key != NULL && ft_strcmp(key, pair->key) > 0)
		pair = pair->next;
	if (pair == NULL || pair->key == NULL || ft_strcmp(key, pair->key) != 0)
		return (NULL);
	else
		return (pair);
}

void					ht_remove(hashtable_t *hashtable, char *key)
{
	int					bin;
	entry_t				*pair;
	entry_t				*old;

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
