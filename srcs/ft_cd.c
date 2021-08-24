/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takim <takim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:37:25 by hoylee            #+#    #+#             */
/*   Updated: 2021/08/23 23:09:19 by takim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_cd_wave(t_cmd *cmd_list, char *tmp, char *pst_buffer)
{
	if (cmd_list->cmdline[1].cmd[0] == '~')
	{
		if (cmd_list->cmdline[1].cmd[1] == '/')
		{
			tmp = cmd_list->cmdline[1].cmd;
			cmd_list -> cmdline[1].cmd
				= ft_strjoin(getenv("HOME"), &cmd_list->cmdline[1].cmd[1]);
			free(tmp);
		}
		else if (cmd_list->cmdline[1].cmd[1] == 0)
		{
			chdir(getenv("HOME"));
			free(pst_buffer);
			return (1);
		}
	}
	if (chdir(cmd_list->cmdline[1].cmd) == -1)
	{
		chdir(pst_buffer);
		cmd_list->err_manage.errcode = 3;
		cmd_list->err_manage.errindex = 1;
		free(pst_buffer);
		return (-1);
	}
	return (0);
}

int	ft_cd(t_cmd *cmd_list)
{
	int		i;
	char	*pst_buffer;	
	char	*tmp;
	int		ret_tmp;

	i = 0;
	tmp = NULL;
	if (cmd_list->cmdline[1].cmd == 0 || cmd_list->cmdline[1].redir_flag == 1)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	if (cmd_list->cmdline[1].cmd[0] == 0)
		return (1);
	pst_buffer = getcwd(0, 0);
	ret_tmp = ft_cd_wave(cmd_list, tmp, pst_buffer);
	if (ret_tmp != 0)
		return (ret_tmp);
	free(pst_buffer);
	return (1);
}
