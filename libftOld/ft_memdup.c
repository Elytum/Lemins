#include <stdlib.h>
#include <libft.h>

void		*ft_memdup(const char *src, size_t len)
{
	char	*buffer;

	if (!(buffer = malloc(sizeof(char) * (len))))
		return (NULL);
	ft_memcpy(buffer, src, len);
	buffer[len] = '\0';
	return (buffer);
}
