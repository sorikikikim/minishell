#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	tmp2;

	tmp = (unsigned char*)s;
	tmp2 = (unsigned char)c;
	while (n--)
	{
		if (*tmp++ == tmp2)
		{
			tmp -= 1;
			return ((void*)tmp);
		}
	}
	return (0);
}
