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

t_hashtable				*ht_create(int size)
{
	t_hashtable			*hashtable;
	int					i;

	hashtable = NULL;
	if (size < 1 ||
		(hashtable = malloc(sizeof(t_hashtable))) == NULL ||
		(hashtable->table = malloc(sizeof(t_entry *) * size)) == NULL)
		exit(write(1, "Error\n", 6));
	i = 0;
	while (i < size)
		hashtable->table[i++] = NULL;
	hashtable->size = size;
	return (hashtable);
}

int						ht_hash(t_hashtable *hashtable, char *key)
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

t_entry					*ht_newpair(char *key, void *value)
{
	t_entry				*newpair;

	if ((newpair = malloc(sizeof(t_entry))) == NULL ||
		(newpair->key = key) == NULL ||
		(newpair->value = value) == NULL)
		exit(write(1, "Error\n", 6));
	newpair->next = NULL;
	return (newpair);
}

void					ht_free(t_hashtable *hashtable)
{
	int					i;
	t_entry				*ptr;
	t_entry				*next;

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

void					ht_clear(t_hashtable *hashtable)
{
	int					i;
	t_entry				*ptr;
	t_entry				*next;

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
