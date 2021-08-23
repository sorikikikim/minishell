#include "../includes/cmd_split.h"

static void	chk_quote(char const *s, int *quote)
{
	if (*s == '"' && (*quote == 0 || *quote == '"'))
	{
		if (*quote == '"')
			*quote = 0;
		else
			*quote = '"';
	}
	else if (*s == '\'' && (*quote == 0 || *quote == '\''))
	{
		if (*quote == '\'')
			*quote = 0;
		else
			*quote = '\'';
	}
}

static int	is_redir(char const *s)
{
	if (*s == '>' || *s == '<')
		return (1);
	else
		return (0);
}

static void	set_redir_cnt(t_split_cnt *vars)
{
	vars->redir = 0;
	vars->cnt++;
}

static void	else_condition(t_split_cnt *vars, char const *s, const char c)
{
	if (*s == c && vars->quote == 0)
	{
		vars->redir = 0;
		vars->begin = 0;
		vars->cnt++;
	}
	else if (is_redir(s) && vars->quote == 0)
	{
		if (vars->redir == 0 && *(s - 1) != ' ')
			vars->cnt++;
		vars->redir++;
	}
	else if (*s != c && *s != '\'' && !is_redir(s)
		&& vars->quote == 0 && is_redir(s - 1))
		set_redir_cnt(vars);
	else if (*s == '\'' && vars->quote == '\'' && is_redir(s - 1))
		set_redir_cnt(vars);
	else if (*s == '"' && vars->quote == '"' && is_redir(s - 1))
		set_redir_cnt(vars);
}

int	ft_split_cnt(char const *s, const char c)
{
	t_split_cnt	vars;

	init_vars(&vars);
	while (*s)
	{
		chk_quote(s, &vars.quote);
		if (vars.begin == 0)
		{
			if (*s != c)
				vars.begin = 1;
			if (*s == '<' || *s == '>')
				vars.redir++;
		}
		else
			else_condition(&vars, s, c);
		s++;
	}
	if (vars.begin == 0)
		return (vars.cnt);
	else
		return (vars.cnt + 1);
}
