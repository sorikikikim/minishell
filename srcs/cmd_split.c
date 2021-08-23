#include "../includes/cmd_split.h"

static char	*ft_alloc_word(int *idx, char const *s, const char c)
{
	int		word_len;
	char	*word;
	int		i;

	word_len = ft_word_len(&s[*idx], c);
	word = (char *)malloc(sizeof(char) + (word_len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = s[*idx + i];
		i++;
	}
	word[i] = '\0';
	*idx += word_len;
	return (word);
}

static int	ft_free(t_token *result, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(result[i++].cmd);
	return (0);
}

static int	cmd_split_sub(const char *s, char c, t_token *result)
{
	int		i;
	int		cursor;

	i = 0;
	cursor = 0;
	while (s[cursor])
	{
		if (s[cursor] == c)
			cursor++;
		else
		{
			result[i].cmd = ft_alloc_word(&cursor, s, c);
			result[i].redir_flag = 0;
			if (result[i].cmd == NULL)
				return (ft_free(result, i));
			i++;
		}
	}
	result[i].cmd = 0;
	return (1);
}

t_token	*cmd_split(char const *s, char c)
{
	t_token	*result;

	if (s == NULL)
		return (NULL);
	result = (t_token *)malloc(sizeof(t_token) * (ft_split_cnt(s, c) + 1));
	if (result == NULL)
		return (NULL);
	if (!cmd_split_sub(s, c, result))
		return (0);
	return (result);
}
