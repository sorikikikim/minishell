#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1tmp;
	unsigned char	*s2tmp;
	int				i;

	s1tmp = (unsigned char*)s1;
	s2tmp = (unsigned char*)s2;
	i = 0;
	if (s1 == 0 && s2 == 0 && n != 0)
		return (0);
	while (n--)
	{
		if (s1tmp[i] != s2tmp[i])
			return (s1tmp[i] - s2tmp[i]);
		i++;
	}
	return (0);
}
