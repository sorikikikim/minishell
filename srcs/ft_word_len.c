#include "../includes/cmd_split.h"

static void	init_vars_word_len(t_word_len *vars)
{
	vars->len = 0;
	vars->begin = 0;
	vars->quote = 0;
}

static void	redir_len(char const *s, int *len)
{
	while (*s)
	{
		if (*s == '>' || *s == '<')
			(*len)++;
		else
			break ;
		s++;
	}
}

static void	chk_quote(char const *s, t_word_len *vars)
{
	if (*s == '"' && (vars->quote == 0 || vars->quote == '"'))
	{
		if (vars->quote == '"')
			vars->quote = 0;
		else
			vars->quote = '"';
	}
	else if (*s == '\'' && (vars->quote == 0 || vars->quote == '\''))
	{
		if (vars->quote == '\'')
			vars->quote = 0;
		else
			vars->quote = '\'';
	}
}

static void	un_redir_len(char const *s, const char c, t_word_len *vars)
{
	while (*s)
	{
		chk_quote(s, vars);
		if (vars->begin == 0)
		{
			if (*s != c)
			{
				vars->begin = 1;
				vars->len++;
			}
		}
		else
		{
			if (*s == c && vars->quote == 0)
				break ;
			else if ((*s == '>' || *s == '<') && vars->quote == 0)
				break ;
			else
				vars->len++;
		}
		s++;
	}
}

int	ft_word_len(char const *s, const char c)
{
	t_word_len	vars;

	init_vars_word_len(&vars);
	if (*s == '>' || *s == '<')
		redir_len(s, &vars.len);
	else
		un_redir_len(s, c, &vars);
	return (vars.len);
}
