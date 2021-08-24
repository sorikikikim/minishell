#include "../includes/minishell.h"

static int	exec_function_sub(t_cmd *cmd_list, int *fds, int *fd)
{
	cmd_list->right_flag = 0;
	if (redir_err_chk(cmd_list) == -1)
		return (-1);
	cmd_list->right_flag = redirect_check(cmd_list, &fds);
	if (cmd_list->right_flag == -1)
		return (-1);
	if (cmd_list->pipe_flag == 1 && cmd_list->right_flag == 0)
		*fd = fds[1];
	else
		*fd = 1;
	return (0);
}

int	exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[])
{
	int	fd;

	if (exec_function_sub(cmd_list, fds, &fd) == -1)
		return (-1);
	if (ft_strncmp("pwd", cmd_list->cmdline[0].cmd, 4) == 0)
		return (ft_pwd(fd));
	else if (ft_strncmp("cd", cmd_list->cmdline[0].cmd, 3) == 0)
		return (ft_cd(cmd_list));
	else if (ft_strncmp("exit", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_exit(cmd_list));
	else if (ft_strncmp("env", cmd_list->cmdline[0].cmd, 4) == 0)
		return (ft_env(*envp, fd));
	else if (ft_strncmp("export", cmd_list->cmdline[0].cmd, 7) == 0)
		return (ft_export(cmd_list, envp, fd));
	else if (ft_strncmp("echo", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_echo(cmd_list, fd));
	else if (ft_strncmp("unset", cmd_list->cmdline[0].cmd, 6) == 0)
		return (ft_unset(cmd_list, *envp));
	else if (non_builtin(cmd_list, argv, *envp, fds) == 0)
	{
		cmd_list->err_manage.errcode = 1;
		return (-1);
	}
	return (0);
}

static void	exec_sub(t_exec *vars, t_cmd *cmd_list)
{
	if (vars->tmp == -1)
		print_errstr(cmd_list);
	else if (vars->tmp == 1)
		g_exit_status = 0;
	dup2(100, STDOUT);
	dup2(101, STDIN);
	if (cmd_list->pipe_flag == 1)
	{
		vars->pid = fork();
		if (vars->pid < 0)
		{
			cmd_list->err_manage.errcode = 1;
			print_errstr(cmd_list);
		}
	}
}

int	exec(t_cmd *cmd_list, char *argv[], char **envp[])
{
	t_exec	vars;

	pipe(vars.fds);
	vars.tmp = exec_function(cmd_list, argv, envp, vars.fds);
	exec_sub(&vars, cmd_list);
	if ((cmd_list->pipe_flag == 1 && vars.pid < 0) || cmd_list->pipe_flag == 0)
		return (g_exit_status);
	if (vars.pid == 0)
	{
		dup2(vars.fds[0], 0);
		close(vars.fds[0]);
		close(vars.fds[1]);
		g_exit_status = exec(cmd_list->next, argv, envp);
		exit(g_exit_status);
	}
	else
	{
		close(vars.fds[1]);
		close(vars.fds[0]);
		vars.wpid = waitpid(vars.pid, &vars.status, 0);
		g_exit_status = vars.status >> 8;
		return (g_exit_status);
	}
}
