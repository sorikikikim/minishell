#include "../includes/alloc_token.h"

int	get_envkey(char *src, char **key)
{
	int	key_len;

	key_len = env_key_size(src);
	*key = ft_substr(src, 1, key_len);
	return (key_len);
}

t_token	*ft_alloc_token(t_token *token, char **envp)
{
	int		cmd_len;
	size_t	i;
	char	*tmp_cmd;

	i = 0;
	while (token[i].cmd)
	{
		cmd_len = 0;
		tmp_cmd = token[i].cmd;
		cmd_len = get_parse_size(tmp_cmd, envp);
		if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>')
		{
			if (redir_chk(token[i].cmd))
				token[i].redir_flag = 1;
			else
				token[i].redir_flag = -1;
		}
		token[i].cmd = (char *)malloc(sizeof(char) * (cmd_len + 1));
		ft_copy_str(tmp_cmd, token[i].cmd, envp);
		free(tmp_cmd);
		i++;
	}
	return (token);
}
