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

hashtable_t				*ht_create(int size)
{
	hashtable_t			*hashtable;
	int					i;

	hashtable = NULL;
	if (size < 1 ||
		(hashtable = malloc(sizeof(hashtable_t))) == NULL ||
		(hashtable->table = malloc(sizeof(entry_t *) * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		hashtable->table[i++] = NULL;
	hashtable->size = size;
	return (hashtable);
}

int						ht_hash(hashtable_t *hashtable, char *key)
{
	unsigned long int	hashval;
	unsigned long int	i;

	hashval = 0;
	i = 0;
	while (hashval < ULONG_MAX && i < ft_strlen(key))
	{
		hashval = hashval << 8;
		hashval += key[i++];
	}
	return (hashval % hashtable->size);
}

entry_t					*ht_newpair(char *key, void *value)
{
	entry_t				*newpair;

	if ((newpair = malloc(sizeof(entry_t))) == NULL ||
		(newpair->key = key) == NULL ||
		(newpair->value = value) == NULL)
		return (NULL);
	newpair->next = NULL;
	return (newpair);
}

void					ht_free(hashtable_t *hashtable)
{
	int					i;
	entry_t				*ptr;
	entry_t				*next;

	i = 0;
	while (i < hashtable->size)
	{
		if (!(ptr = hashtable->table[i++]))
		{
			if (i >= hashtable->size)
				return ;
			continue ;
		}
		while (ptr != NULL && ptr->key != NULL)
		{
			next = ptr->next;
			free(ptr->key);
			free(ptr->value);
			free(ptr);
			ptr = next;
		}
	}
	free(hashtable->table);
	free(hashtable);
}

void					ht_clear(hashtable_t *hashtable)
{
	int					i;
	entry_t				*ptr;
	entry_t				*next;

	i = hashtable->size;
	while (i < hashtable->size)
	{
		if (!(ptr = hashtable->table[i++]))
			continue ;
		next = ptr->next;
		free(ptr->key);
		free(ptr->value);
		ptr = next;
		while (ptr != NULL && ptr->key != NULL)
		{
			next = ptr->next;
			free(ptr->key);
			free(ptr->value);
			free(ptr);
			ptr = next;
		}
	}
}
