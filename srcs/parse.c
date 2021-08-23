#include "../includes/minishell.h"

static void	cmd_list_append(int start, t_parse *p, t_cmd **cmd_list)
{
	if (start == 0)
	{
		*cmd_list = p->new;
		p->tmp = *cmd_list;
	}
	else
	{
		(*cmd_list)->next = p->new;
		*cmd_list = (*cmd_list)->next;
	}
}

static void	init_p(t_parse *p)
{
	p->quote_flag = 0;
	p->i = 0;
	p->start = 0;
	p->pipe_flag = 1;
}

static void	chk_quote(char *line, int i, int	*quote_flag)
{
	if ((line[i] == '\"' || line[i] == '\'') && *quote_flag == 0)
		*quote_flag = 1;
	else if ((line[i] == '\"' || line[i] == '\'') && *quote_flag == 1)
		*quote_flag = 0;
}

void	parse(t_cmd **cmd_list, char *line, char **envp)
{
	t_parse		p;

	init_p(&p);
	while (1)
	{
		chk_quote(line, p.i, &p.quote_flag);
		if (line[p.i] == '\0' || (line[p.i] == '|' && p.quote_flag == 0))
		{
			if (line[p.i] == '|')
				line[p.i] = '\0';
			else
				p.pipe_flag = 0;
			p.new = ft_new(&line[p.start], p.pipe_flag, envp, p.start);
			if ((p.new) == 0)
				return ;
			cmd_list_append(p.start, &p, cmd_list);
			if (p.pipe_flag == 0)
				break ;
			p.start = p.i + 1;
		}
		p.i++;
	}
	*cmd_list = p.tmp;
}
