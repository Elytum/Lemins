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

entry_t					*ht_fln(entry_t *next, const char *key, void *value)
{
	entry_t				*last;

	while (next != NULL && next->key != NULL && ft_strcmp(key, next->key) > 0)
	{
		last = next;
		next = next->next;
	}
	if (next != NULL && next->key != NULL && ft_strcmp(key, next->key) == 0)
	{
		free(next->value);
		next->value = value;
		return (NULL);
	}
	return (last);
}

void					ht_set(hashtable_t *hashtable, char *key, void *value)
{
	int					bin;
	entry_t				*newpair;
	entry_t				*next;
	entry_t				*last;

	bin = ht_hash(hashtable, key);
	if (!(last = ht_fln(hashtable->table[bin], key, value)))
		return ;
	next = last->next;
	newpair = ht_newpair(key, value);
	if (next == hashtable->table[bin])
	{
		newpair->next = next;
		hashtable->table[bin] = newpair;
	}
	else
	{
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
