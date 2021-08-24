#include "../includes/minishell.h"

void	error_write(char *error_str, char *err_cmdline, char *err_cmdline2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (err_cmdline == 0 || error_str == 0)
		return ;
	while (error_str[++i])
	{
		j = -1;
		if (error_str[i] == '%' && error_str[i + 1] == 's' && err_cmdline != 0)
		{
			while (err_cmdline[++j])
				write(2, &err_cmdline[j], 1);
			err_cmdline = err_cmdline2;
			i++;
		}
		else
			write(2, &error_str[i], 1);
	}
}
