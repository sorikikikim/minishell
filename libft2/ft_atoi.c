#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	ret;
	int				sign;

	ret = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*(str++) == '-')
			sign *= -1;
	}
	while ('0' <= *str && *str <= '9')
	{
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	return ((int)(ret * sign));
}
