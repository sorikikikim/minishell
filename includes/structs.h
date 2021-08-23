#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_err
{
	int				errcode;
	int				errindex;
	char			*errtoken;
}				t_err;

typedef struct	s_token
{
	char		*cmd;
	char		redir_flag;
}				t_token;

typedef struct	s_cmd
{
	t_token			*cmdline;
	int				pipe_flag;
	int				exit_flag;
	int				right_flag;
	char			quote;
	char			*(redirect_filename[4]);
	//index 0 : left redirect char (<, <<);
	//index 1 : left redirect filename;
	//index 2 : righ redirect char (>, >>);
	//index 3 : righ redirect filename;
	struct s_err	err_manage;
	struct s_cmd	*next;
}				t_cmd;

typedef	struct	s_parse
{
	t_cmd	*tmp;
	t_cmd	*new;
	int		i;
	int		start;
	int		pipe_flag;
	int		quote_flag;
}	t_parse;

typedef struct	s_split_cnt
{
	int cnt;
	int begin;
	int quote;
	int redir;
}	t_split_cnt;

typedef struct	s_word_len
{
	int len;
	int begin;
	int quote;
}	t_word_len;
#endif
