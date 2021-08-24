#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*result;
	char	*start;

	result = (char*)dst;
	start = (char*)src;
	if (!dst && !src)
		return (0);
	while (n--)
	{
		*result++ = *start++;
	}
	return (dst);
}
