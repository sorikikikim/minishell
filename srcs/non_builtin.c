#include "../includes/minishell.h"

static int	env_path_split(t_non_builtin *vars, char **envp)
{
	vars->env_path = get_env_value("PATH", envp);
	if (vars->env_path == NULL)
	{
		free(vars->buf);
		return (0);
	}
	vars->paths = ft_split(vars->env_path, ':');
	if (vars->paths == NULL)
	{
		free(vars->buf);
		return (0);
	}
	return (1);
}

static int	init_non_builtin(t_argv_envp *ae,
	t_non_builtin *vars, char **argv, char **envp)
{
	vars->i = -1;
	ae->argv = argv;
	ae->envp = envp;
	vars->flag = 0;
	vars->buf = (struct stat *)malloc(sizeof(struct stat));
	if (!(vars->buf))
		return (0);
	return (1);
}

int	cmd_path(t_cmd *cmd_list, t_non_builtin *vars, t_argv_envp *ae, int *fds)
{
	if (cmd_list->cmdline[0].cmd[0] != '\0'
		&& stat(cmd_list->cmdline[0].cmd, vars->buf) == 0)
	{
		if (non_builtin_exec(cmd_list, ae,
				cmd_list->cmdline[0].cmd, fds) == -1)
		{
			free(vars->buf);
			return (0);
		}
		vars->flag = 1;
	}
	return (1);
}

static int	cmd_no_path(t_cmd *cmd_list,
	t_non_builtin *vars, t_argv_envp *ae, int *fds)
{
	while (vars->paths[++(vars->i)] != NULL)
	{
		vars->tmp = strjoin_path(vars->paths[vars->i],
				cmd_list->cmdline[0].cmd);
		if (vars->tmp == 0)
		{
			free(vars->buf);
			return (0);
		}
		if (cmd_list->cmdline[0].cmd[0] != '\0'
			&& stat(vars->tmp, vars->buf) == 0)
		{
			if (non_builtin_exec(cmd_list, ae, vars->tmp, fds) == -1)
			{
				free(vars->buf);
				return (0);
			}
			vars->flag = 1;
			free(vars->tmp);
			break ;
		}
		free(vars->tmp);
	}
	vars->i = -1;
	return (1);
}

int	non_builtin(t_cmd *cmd_list, char **argv, char **envp, int fds[])
{
	t_non_builtin	vars;
	t_argv_envp		ae;

	if (!(init_non_builtin(&ae, &vars, argv, envp)))
		return (0);
	if (!cmd_path(cmd_list, &vars, &ae, fds))
		return (0);
	if (!(cmd_list->cmdline[0].cmd[0] != '\0'
			&& stat(cmd_list->cmdline[0].cmd, vars.buf) == 0))
	{
		if (!(env_path_split(&vars, envp)))
			return (0);
		if (!cmd_no_path(cmd_list, &vars, &ae, fds))
			return (0);
		while (vars.paths[++(vars.i)] != NULL)
			free(vars.paths[(vars.i)]);
		free(vars.paths);
	}
	if (vars.flag == 0 && cmd_list->cmdline[0].redir_flag != 1)
	{
		free(vars.buf);
		return (0);
	}
	free(vars.buf);
	return (1);
}
