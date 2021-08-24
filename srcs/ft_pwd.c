#include "../includes/minishell.h"

int	ft_pwd(int fd)
{
	char		*str;

	str = getcwd(NULL, 0);
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
	free(str);
	return (1);
}
