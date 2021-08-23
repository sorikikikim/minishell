#include "../includes/get_parse_size.h"

int		unclosed_quote(char *str, char quote)
{
	int	index;

	index = 1;
	while (str[index] && str[index] != quote)
		index++;
	if (str[index] == '\0')
		return (0);
	return (1);
}

int		d_quote_cnt(char *str, int *size, char **envp)
{
	int index;

	index = 1;
	while (str[index] && str[index] != '\"')
	{
		if (str[index] == '$')
		{
			index += (env_cnt(&str[index], size, envp) + 1);
		}
		else
		{
			index++;
			(*size)++;
		}
	}
	return (index);
}

int		s_quote_cnt(char *str, int *size)
{
	int index;

	index = 1;
	while (str[index] && str[index] != '\'')
	{
		index++;
		(*size)++;
	}
	return (index);
}

int get_parse_size(char *str, char **envp)
{
	int	index;
	int size;

	size = 0;
	index = -1;
	while (str[++index])
	{
		if (str[index] == '\'' && unclosed_quote(&str[index], '\''))
			index += s_quote_cnt(&str[index], &size);
		else if (str[index] == '\"' && unclosed_quote(&str[index], '\"'))
			index += d_quote_cnt(&str[index], &size, envp);
		else if (str[index] == '$')
			index += env_cnt(&str[index], &size, envp);
		else if (str[index])
			size++;
	}
	return (size); //flag가 1이면 안닫힌 따옴표 에러를 의미.
}
