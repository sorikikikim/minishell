#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/types.h>

typedef struct s_err
{
	int				errcode;
	int				errindex;
	char			*errtoken;
}				t_err;

typedef struct s_token
{
	char		*cmd;
	char		redir_flag;
}				t_token;

typedef struct s_cmd
{
	t_token			*cmdline;
	int				pipe_flag;
	int				exit_flag;
	int				right_flag;
	char			quote;
	char			*(redirect_filename[4]);
	struct s_err	err_manage;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parse
{
	t_cmd	*tmp;
	t_cmd	*new;
	int		i;
	int		start;
	int		pipe_flag;
	int		quote_flag;
}	t_parse;

typedef struct s_split_cnt
{
	int	cnt;
	int	begin;
	int	quote;
	int	redir;
}	t_split_cnt;

typedef struct s_word_len
{
	int	len;
	int	begin;
	int	quote;
}	t_word_len;

typedef struct s_exec
{
	int		fds[2];
	int		status;
	pid_t	pid;
	pid_t	wpid;
	int		tmp;
}	t_exec;

typedef struct s_non_builtin
{
	struct stat	*buf;
	char		*env_path;
	char		**paths;
	char		*tmp;
	int			i;
	int			flag;
}	t_non_builtin;

typedef struct s_argv_envp
{
	char	**argv;
	char	**envp;
}	t_argv_envp;
#endif
