#include "../includes/minishell.h"

int	check_digit(t_cmd *cmd_list)
{
	int			i;

	i = -1;
	if (cmd_list->cmdline[1].cmd[0] == '-')
		i++;
	while (cmd_list->cmdline[1].cmd[++i] != '\0')
	{
		if (ft_isdigit(cmd_list->cmdline[1].cmd[i]) == 0)
		{
			if (cmd_list->exit_flag == 1)
			{
				cmd_list->err_manage.errcode = 4;
				cmd_list->err_manage.errindex = 1;
				print_errstr(cmd_list);
				exit(-1);
			}
			else
				return (0);
		}
	}
	return (1);
}

static int	ft_exit_sub(t_cmd *cmd_list)
{
	if (cmd_list->exit_flag == 1)
		printf("exit\n");
	if (cmd_list->cmdline[1].cmd != NULL)
	{
		if (check_digit(cmd_list) == 0)
		{
			cmd_list->err_manage.errcode = 4;
			cmd_list->err_manage.errindex = 1;
			return (-1);
		}
		if (cmd_list->cmdline[2].cmd != NULL)
		{
			cmd_list->err_manage.errcode = 2;
			return (-1);
		}
	}
	else if (cmd_list->exit_flag == 1)
		exit(0);
	return (0);
}

int	ft_exit(t_cmd *cmd_list)
{
	long long	result;
	int			err_flag;

	err_flag = 0;
	if (ft_exit_sub(cmd_list) == -1)
		return (-1);
	if (cmd_list->exit_flag == 1)
	{
		result = ft_atoi_chk_overflow(cmd_list->cmdline[1].cmd, &err_flag);
		if (err_flag == 1)
		{
			cmd_list->err_manage.errcode = 4;
			cmd_list->err_manage.errindex = 1;
			print_errstr(cmd_list);
			exit(-1);
		}
		exit(result % 256);
	}
	return (1);
}
