#include "../includes/minishell.h"

static char	**set_argv(t_cmd *cmd_list, int *i, char *path)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * (token_num(cmd_list->cmdline) + 1));
	if (!ret)
		return (NULL);
	*i = 1;
	ret[0] = path;
	while (cmd_list->cmdline[*i].cmd != NULL
		&& cmd_list->cmdline[*i].redir_flag == 0)
	{
		ret[*i] = cmd_list->cmdline[*i].cmd;
		(*i)++;
	}
	ret[*i] = NULL;
	return (ret);
}

int	non_builtin_exec(t_cmd *cmd_list, t_argv_envp *ae, char *path, int fds[])
{
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			i;

	ae->argv = set_argv(cmd_list, &i, path);
	pid = fork();
	if (pid < -1)
		return (-1);
	if (pid == 0)
	{
		if (cmd_list->pipe_flag == 1 && cmd_list->right_flag == 0)
			dup2(fds[1], 1);
		if (execve(path, ae->argv, ae->envp) == -1)
			return (-1);
	}
	else if (pid != 0)
	{
		wpid = waitpid(pid, &status, 0);
		g_exit_status = status >> 8;
	}
	return (0);
}
