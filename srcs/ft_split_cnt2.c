#include "../includes/cmd_split.h"

void	init_vars(t_split_cnt *vars)
{
	vars->cnt = 0;
	vars->begin = 0;
	vars->quote = 0;
	vars->redir = 0;
}
