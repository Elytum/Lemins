/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:20:13 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 18:11:29 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABLE_H
# define HTABLE_H
# include <stdlib.h>

typedef struct			s_entry
{
	char				*key;
	void				*value;
	struct s_entry		*next;
}						t_entry;

typedef struct			s_hashtable
{
	int					size;
	struct s_entry		**table;
}						t_hashtable;

t_hashtable				*ht_create(int size);
int						ht_hash(t_hashtable *hashtable, char *key);
t_entry					*ht_newpair(char *key, void *value);
void					ht_set(t_hashtable *hashtable, char *key, void *value);
void					*ht_get(t_hashtable *hashtable, char *key);
t_entry					*ht_get_pair(t_hashtable *hashtable, char *key);
void					ht_remove(t_hashtable *hashtable, char *key);
void					ht_free(t_hashtable *hashtable);
void					ht_clear(t_hashtable *hashtable);

#endif
