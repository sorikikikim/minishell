#include "../includes/minishell.h"

void	ft_print_unset_err(t_cmd *cmd_list)
{
	int	i;

	i = 1;
	while (cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].redir_flag == 0)
	{
		if (ft_valid_key(cmd_list->cmdline[i].cmd) == 0)
			error_write("minishell: %s: `%s': not a valid identifier\n",
				cmd_list->cmdline[0].cmd, cmd_list->cmdline[i].cmd);
		i++;
	}
}

void	ft_print_export_err(t_cmd *cmd_list)
{
	int	i;

	i = 1;
	while (cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].redir_flag == 0)
	{
		if (isvalid_export(cmd_list->cmdline[i].cmd) == 0)
			error_write("minishell: %s: `%s': not a valid identifier\n",
				cmd_list->cmdline[0].cmd, cmd_list->cmdline[i].cmd);
		i++;
	}
}

static void	print_errstr2(t_cmd *cmd_list)
{
	if (cmd_list->err_manage.errcode == 4)
	{
		error_write("minishell: %s: %s: numeric argument required\n",
			cmd_list->cmdline[0].cmd,
			cmd_list->cmdline[cmd_list->err_manage.errindex].cmd);
		g_exit_status = 255;
	}
	else if (cmd_list->err_manage.errcode == 5)
	{
		ft_print_export_err(cmd_list);
		g_exit_status = 1;
	}
	else if (cmd_list->err_manage.errcode == 6)
	{
		ft_print_unset_err(cmd_list);
		g_exit_status = 1;
	}
}

static void	print_errstr3(t_cmd *cmd_list)
{
	if (cmd_list->err_manage.errcode == 7)
	{
		if (cmd_list->err_manage.errtoken)
			error_write("minishell: syntax error near unexpected token `%s'\n",
				cmd_list->err_manage.errtoken, 0);
		else
			error_write("minishell: syntax error near unexpected token `%s\'\n",
				cmd_list->cmdline[cmd_list->err_manage.errindex].cmd, 0);
		g_exit_status = 258;
	}
	else if (cmd_list->err_manage.errcode == 8)
	{
		error_write("minishell: syntax error near unexpected token `newline\'\n",
			cmd_list->cmdline[cmd_list->err_manage.errindex].cmd, 0);
		g_exit_status = 258;
	}
}

void	print_errstr(t_cmd *cmd_list)
{
	if (cmd_list->err_manage.errcode == 1)
	{
		error_write("minishell: %s: command not found\n",
			cmd_list->cmdline[0].cmd, 0);
		g_exit_status = 127;
	}
	else if (cmd_list->err_manage.errcode == 2)
	{
		error_write("minishell: %s: too many arguments\n",
			cmd_list->cmdline[0].cmd, 0);
		g_exit_status = 1;
	}
	else if (cmd_list->err_manage.errcode == 3)
	{
		error_write("minishell: %s: No such file or directory\n",
			cmd_list->cmdline[cmd_list->err_manage.errindex].cmd, 0);
		g_exit_status = 1;
	}
	print_errstr2(cmd_list);
	print_errstr3(cmd_list);
}
