#include <htable.h>

#include <string.h>
#include <limits.h>

hashtable_t				*ht_create(int size)
{
	hashtable_t			*hashtable;
	int					i;

	hashtable = NULL;
	if (size < 1 ||
		(hashtable = malloc(sizeof(hashtable_t))) == NULL ||
		(hashtable->table = malloc(sizeof(entry_t *) * size)) == NULL)
		return NULL;
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
	while (hashval < ULONG_MAX && i < strlen(key))
	{
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}
	return (hashval % hashtable->size);
}

entry_t					*ht_newpair( char *key, void *value )
{
	entry_t				*newpair;

	if ((newpair = malloc(sizeof(entry_t))) == NULL ||
		(newpair->key = key) == NULL ||
		(newpair->value = value) == NULL )
		return NULL;
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

	i = hashtable->size; // !!! 0
	while (i < hashtable->size)
	{
		if (!(ptr = hashtable->table[i++]))
			continue ;
		next = ptr->next;
		free(ptr->key);
		free(ptr->value);
		ptr = next;
		while (ptr != NULL && ptr->key != NULL) {
			next = ptr->next;
			free(ptr->key);
			free(ptr->value);
			free(ptr);
			ptr = next;
		}
	}
}

void 					ht_set(hashtable_t *hashtable, char *key, void *value)
{
	int					bin ;
	entry_t				*newpair = NULL;
	entry_t				*next = NULL;
	entry_t				*last = NULL;

	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0)
	{
		last = next;
		next = next->next;
	}
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0)
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
			hashtable->table[ bin ] = newpair;
		}
		else
		{
			last->next = newpair;
			if (next)
				newpair->next = next;
		}
	}
}

void 					*ht_get(hashtable_t *hashtable, char *key)
{
	int					bin;
	entry_t				*pair;

	bin = ht_hash( hashtable, key );
	pair = hashtable->table[ bin ];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
		pair = pair->next;
	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
		return NULL;
	else
		return pair->value;
}

entry_t 				*ht_get_pair(hashtable_t *hashtable, char *key)
{
	int					bin;
	entry_t				*pair;

	bin = ht_hash( hashtable, key );
	pair = hashtable->table[ bin ];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
		pair = pair->next;
	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
		return NULL;
	else
		return pair;
}

void					ht_remove(hashtable_t *hashtable, char *key)
{
	int					bin;
	entry_t				*pair;
	entry_t				*old;

	bin = ht_hash(hashtable, key);
	pair = hashtable->table[bin];
	old = NULL;
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0 )
	{
		old = pair;
		pair = pair->next;
	}
	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0 )
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
