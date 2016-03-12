/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_trim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <smarie-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:37:59 by smarie-c          #+#    #+#             */
/*   Updated: 2014/03/26 06:03:48 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		ft_word(char const *s, char c, size_t *i)
{
	char	quote;

	while (s[*i] && (s[*i] != c || ft_oddprev(s, *i - 1, '\\')))
	{
		if ((s[*i] == '"' || s[*i] == '\'' || s[*i] == '`')
			&& ft_oddprev(s, *i - 1, '\\') == 0)
		{
			quote = s[*i];
			(*i)++;
			while (s[*i] && (s[*i] != quote
						|| ft_oddprev(s, *i - 1, '\\')))
				(*i)++;
		}
		if (s[*i])
			(*i)++;
	}
}

static size_t	ft_nbsplit(char const *s, char c)
{
	size_t		count;
	size_t		i;

	count = 0;
	i = 0;
	while (s != NULL && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		ft_word(s, c, &i);
	}
	return (count);
}

static char		**ft_getsplit(char const *s, char c, char **split, size_t len)
{
	size_t		i;
	size_t		start;
	size_t		end;
	size_t		nb;
	char		*tmp;

	i = 0;
	nb = 0;
	while (nb < len)
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		ft_word(s, c, &i);
		end = i;
		tmp = ft_strsub(s, start, end - start);
		split[nb] = ft_strtrim(tmp);
		free(tmp);
		nb++;
	}
	return (split);
}

char			**ft_strsplit_trim(char const *s, char c)
{
	char		**split;
	size_t		count;

	count = ft_nbsplit(s, c);
	split = (char **)malloc(sizeof(*split) * (count + 1));
	if (split == NULL)
		return (NULL);
	split = ft_getsplit(s, c, split, count);
	split[count] = NULL;
	return (split);
}
