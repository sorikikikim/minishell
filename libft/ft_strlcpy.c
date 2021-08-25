#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 1 || src[0] == '\0')
		dest[0] = '\0';
	else if (size == 0)
		j = 0;
	else
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		if (i < size)
			dest[i] = '\0';
	}
	while (src[j] != 0)
		j++;
	return (j);
}
