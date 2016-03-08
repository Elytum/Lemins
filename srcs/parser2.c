/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int			get_names(char *line, char *linked[2])
{
	char	*delimiter;

	delimiter = ft_strchr(line, '-');
	if (!delimiter)
		return (0);
	*delimiter = '\0';
	linked[0] = line;
	linked[1] = delimiter + 1;
	return (1);
}

void		*get_name(char *line)
{
	char	*ptr;
	char	loop;

	loop = 2;
	if ((ptr = line + ft_strlen(line) - 1) <= line)
		return (NULL);
	while (ptr > line && (*ptr == ' ' || *ptr == '\t'))
		--ptr;
	while (loop--)
	{
		if (!(*ptr >= '0' && *ptr <= '9'))
			return (NULL);
		while (ptr > line && (*ptr >= '0' && *ptr <= '9'))
			--ptr;
		if (*ptr == '+' || *ptr == '-')
			--ptr;
		if (ptr == line || (*ptr != ' ' && *ptr != '\t'))
			return (NULL);
		while (ptr > line && (*ptr == ' ' || *ptr == '\t'))
			--ptr;
	}
	return (ft_memdup(line, ptr - line + 1));
}
