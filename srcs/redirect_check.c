#include "../includes/minishell.h"

int	check_fd_error(t_cmd *cmd_list, int errorcode, int error_index, int fd)
{
	if (fd <= 0)
	{
		cmd_list->err_manage.errcode = errorcode;
		cmd_list->err_manage.errindex = error_index;
		return (-1);
	}
	return (0);
}

static int	no_file_error(t_cmd *cmd_list, int i, int type, int *last_index)
{
	if (cmd_list->cmdline[i + 1].cmd == 0)
	{
		cmd_list->err_manage.errcode = 8;
		return (-1);
	}
	else if (cmd_list->cmdline[i + 1].redir_flag == 1)
	{
		cmd_list->err_manage.errcode = 7;
		cmd_list->err_manage.errindex = i + 1;
		return (-1);
	}
	save_filename(cmd_list, i, type, type + 1);
	last_index[type / 2] = i + 1;
	return (0);
}

static int	file_open_test(t_cmd *cmd_list, int i)
{
	int	fd;

	if (ft_strncmp("<", cmd_list->cmdline[i].cmd, 2) == 0)
	{
		fd = open(cmd_list->cmdline[i + 1].cmd,
				O_WRONLY | O_APPEND, 0744);
		if (check_fd_error(cmd_list, 3, i + 1, fd) == -1)
			return (-1);
		close(fd);
	}
	else
	{
		if (ft_strncmp(">", cmd_list->cmdline[i].cmd, 2) == 0)
			fd = open(cmd_list->cmdline[i + 1].cmd,
					O_WRONLY | O_CREAT | O_TRUNC, 0744);
		else if (ft_strncmp(">>", cmd_list->cmdline[i].cmd, 3) == 0)
			fd = open(cmd_list->cmdline[i + 1].cmd,
					O_WRONLY | O_CREAT | O_APPEND, 0744);
		else
			return (0);
		if (check_fd_error(cmd_list, 3, i + 1, fd) == -1)
			return (-1);
		close(fd);
	}
	return (0);
}

static int	redirect_check_augment(t_cmd *cmd_list, int *last_index, int *i)
{
	if (cmd_list->cmdline[*i].redir_flag == 0)
		;
	else if (ft_strncmp("<", cmd_list->cmdline[*i].cmd, 2) == 0
		|| ft_strncmp("<<",
			cmd_list->cmdline[*i].cmd, 3) == 0)
	{
		if (no_file_error(cmd_list, *i, 0, last_index) == -1)
			return (-1);
		if (file_open_test(cmd_list, *i) == -1)
			return (-1);
	}
	else if (ft_strncmp(">", cmd_list->cmdline[*i].cmd, 2) == 0
		|| ft_strncmp(">>",
			cmd_list->cmdline[*i].cmd, 3) == 0)
	{
		if (no_file_error(cmd_list, *i, 2, last_index) == -1)
			return (-1);
		if (file_open_test(cmd_list, *i) == -1)
			return (-1);
	}
	return (0);
}

int	redirect_check(t_cmd *cmd_list, int **fds)
{
	int	i;
	int	last_index[2];

	i = -1;
	while (++i < 4)
		cmd_list->redirect_filename[i] = 0;
	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (redirect_check_augment(cmd_list, last_index, &i) == -1)
			return (-1);
		i++;
	}
	if ((cmd_list->redirect_filename[0] || cmd_list->redirect_filename[2]))
		return (redirect(cmd_list, fds, last_index));
	else
		return (0);
}
