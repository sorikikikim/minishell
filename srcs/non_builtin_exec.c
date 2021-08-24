#include "../includes/minishell.h"

static void	set_argv(t_cmd *cmd_list, int *i, t_argv_envp *ae, char *path)
{
	*i = 1;
	ae->argv[0] = path;
	while (cmd_list->cmdline[*i].cmd != NULL
		&& cmd_list->cmdline[*i].redir_flag == 0)
	{
		ae->argv[*i] = cmd_list->cmdline[*i].cmd;
		(*i)++;
	}
	ae->argv[*i] = NULL;
}

int	non_builtin_exec(t_cmd *cmd_list, t_argv_envp *ae, char *path, int fds[])
{
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			i;

	set_argv(cmd_list, &i, ae, path);
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
