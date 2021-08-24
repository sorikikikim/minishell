#include "../includes/alloc_token.h"

int	alloc_env_one_dollar(char *src, char **dest)
{
	if (src[1] == ' ' || src[1] == '\0' || src[1] == '\"')
	{
		**dest = '$';
		*dest += 1;
		return (0);
	}
	return (1);
}

int	alloc_env(char *src, char **dest, char **envp)
{
	int		src_idx;
	char	*key;
	char	*env_val;
	int		env_len;
	char	*status;

	src_idx = 0;
	if (src[1] == '?')
	{
		status = ft_itoa(g_exit_status);
		ft_memcpy(*dest, status, ft_strlen(status));
		*dest += ft_strlen(status);
		free(status);
		return (1);
	}
	if (!alloc_env_one_dollar(src, dest))
		return (0);
	src_idx = get_envkey(src, &key);
	env_val = get_env_value(key, envp);
	env_len = ft_strlen(env_val);
	ft_memcpy(*dest, env_val, env_len);
	*dest += env_len;
	free(key);
	return (src_idx);
}

int	alloc_d_quote_cnt(char *src, char **dest, char **envp)
{
	int	src_idx;

	src_idx = 1;
	while (src[src_idx] && src[src_idx] != '\"')
	{
		if (src[src_idx] == '$')
			src_idx += (alloc_env(&src[src_idx], dest, envp) + 1);
		else
		{
			**dest = src[src_idx];
			(*dest)++;
			src_idx++;
		}
	}
	return (src_idx);
}

int	alloc_s_quote_cnt(char *src, char **dest)
{
	int	src_idx;
	int	dest_len;

	src_idx = 1;
	dest_len = 0;
	while (src[src_idx] && src[src_idx] != '\'')
	{
		src_idx++;
		dest_len++;
	}
	ft_memcpy(*dest, src + 1, dest_len);
	*dest += dest_len;
	return (src_idx);
}

void	ft_copy_str(char *src, char *dest, char **envp)
{
	int		src_idx;
	int		size;
	char	*dest_end;

	size = 0;
	src_idx = -1;
	dest_end = dest;
	while (src[++src_idx])
	{
		if (src[src_idx] == '\'' && unclosed_quote(&src[src_idx], '\''))
			src_idx += alloc_s_quote_cnt(&src[src_idx], &dest_end);
		else if (src[src_idx] == '\"' && unclosed_quote(&src[src_idx], '\"'))
			src_idx += alloc_d_quote_cnt(&src[src_idx], &dest_end, envp);
		else if (src[src_idx] == '$')
			src_idx += alloc_env(&src[src_idx], &dest_end, envp);
		else if (src[src_idx])
		{
			*dest_end = src[src_idx];
			dest_end++;
		}
	}
	*dest_end = '\0';
}
