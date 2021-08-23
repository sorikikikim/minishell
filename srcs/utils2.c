#include "../includes/minishell.h"

char	check_quote(char *line)
{
	char		result;
	int			i;

	i = -1;
	result = 0;
	while (line[++i] != '\0')//원래 맨밑에 i++;
	{
		if (line[i] == '"' && (result == 0 || result == '"'))
		{
			if (result == '"')
				result = 0;
			else
				result = '"';
			str_forward(line, &i);
		}
		else if (line[i] == '\'' && (result == 0 || result == '\''))
		{
			if (result == '\'')
				result = 0;
			else
				result = '\'';
			str_forward(line, &i);
		}
	}
	return (result);
}

static long long	ft_atoi_sub(const char *str, int *mark_org)
{
	int				i;
	int				mark;
	long long		result;

	i = 0;
	mark = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			mark = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			break ;
		i++;
	}
	*mark_org = mark;
	return (result);
}

long long	ft_atoi_chk_overflow(const char *str, int *err_flag)
{
	int				mark;
	long long		result;

	result = 0;
	result = ft_atoi_sub(str, &mark);
	if (result < 0)
		*err_flag = 1;
	if (mark == -1 && result == (-9223372036854775807 - 1))
	{
		*err_flag = 0;
		return (result);
	}
	return (mark * result);
}
