#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	while (i != len && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char*)&s[i]);
	return (0);
}
