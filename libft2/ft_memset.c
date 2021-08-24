#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;
	size_t			i;

	i = -1;
	tmp = b;
	while (++i < len)
		*tmp++ = (unsigned char)c;
	return (b);
}
