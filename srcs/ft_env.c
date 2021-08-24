#include "../includes/minishell.h"

int	ft_env(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (haveequal(envp[i]))
		{
			ft_putstr_fd(envp[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
	return (1);
}

char	**copy_envp(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!(new))
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}
