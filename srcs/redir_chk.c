#include "../includes/redir_chk.h"

int	redir_chk(char *str)
{
	size_t	str_len;

	str_len = ft_strlen(str);
	if (!ft_strncmp("<<", str, str_len) || !ft_strncmp(">>", str, str_len)
		|| !ft_strncmp("<", str, str_len) || !ft_strncmp(">", str, str_len))
		return (1);
	else
		return (0);
}

static char	*alloc_unexpected_token_augment(char *redir)
{
	char	*result;

	result = NULL;
	if (ft_strncmp(redir, "<", 1) == 0)
	{
		if (ft_strncmp(redir + 1, "<<", 2) == 0
			|| ft_strncmp(redir + 1, ">>", 2) == 0)
			result = ft_substr(redir, 1, 2);
		else if (ft_strncmp(redir + 1, "<", 1) == 0
			|| ft_strncmp(redir + 1, ">", 1) == 0)
			result = ft_substr(redir, 1, 1);
	}
	else if (ft_strncmp(redir, ">", 1) == 0)
	{
		if (ft_strncmp(redir + 1, "<<", 2) == 0
			|| ft_strncmp(redir + 1, ">>", 2) == 0)
			result = ft_substr(redir, 1, 2);
		else if (ft_strncmp(redir + 1, "<", 1) == 0
			|| ft_strncmp(redir + 1, ">", 1) == 0)
			result = ft_substr(redir, 1, 1);
	}
	return (result);
}

char	*alloc_unexpected_token(char *redir)
{
	char	*result;

	result = NULL;
	if (ft_strncmp(redir, "<<", 2) == 0)
	{
		if (ft_strncmp(redir + 2, "<<", 2) == 0
			|| ft_strncmp(redir + 2, ">>", 2) == 0)
			result = ft_substr(redir, 2, 2);
		else if (ft_strncmp(redir + 2, "<", 1) == 0
			|| ft_strncmp(redir + 2, ">", 1) == 0)
			result = ft_substr(redir, 2, 1);
	}
	else if (ft_strncmp(redir, ">>", 2) == 0)
	{
		if (ft_strncmp(redir + 2, "<<", 2) == 0
			|| ft_strncmp(redir + 2, ">>", 2) == 0)
			result = ft_substr(redir, 2, 2);
		else if (ft_strncmp(redir + 2, "<", 1) == 0
			|| ft_strncmp(redir + 2, ">", 1) == 0)
			result = ft_substr(redir, 2, 1);
	}
	else
		result = alloc_unexpected_token_augment(redir);
	return (result);
}

int	redir_err_chk(t_cmd *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (cmd_list->cmdline[i].redir_flag == -1)
		{
			cmd_list->err_manage.errtoken
				= alloc_unexpected_token(cmd_list->cmdline[i].cmd);
			cmd_list->err_manage.errcode = 7;
			return (-1);
		}
		i++;
	}
	return (1);
}
