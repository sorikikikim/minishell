#ifndef ALLOC_TOKEN_H
# define ALLOC_TOKEN_H
# include <stdlib.h>
# include "cmd_split.h"
# include "get_parse_size.h"
# include "ft_getenv.h"
# include "redir_chk.h"

extern int	g_exit_status;

void	ft_copy_str(char *src, char *dest, char **envp);
int		get_envkey(char *src, char **key);
int		env_value_size(char *str, int size, char **envp);
int		env_key_size(char *str);
int		env_cnt(char *str, int *size, char **envp);
int		alloc_d_quote_cnt(char *src, char **dest, char **envp);
int		alloc_s_quote_cnt(char *src, char **dest);
t_token	*ft_alloc_token(t_token *token, char **envp);

#endif
