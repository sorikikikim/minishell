#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t dest_len;
	size_t src_len;
	size_t i;

	dest_len = 0;
	src_len = 0;
	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (src_len + size);
	while (*dest)
		dest++;
	while ((i < size - dest_len - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len + dest_len);
}
