#ifndef CMD_SPLIT_H
# define CMD_SPLIT_H
# include <stdlib.h>
# include "structs.h"

t_token			*cmd_split(char const *s, char c);
int				ft_word_len(char const *s, const char c);
int				ft_split_cnt(char const *s, const char c);
void			init_vars(t_split_cnt *vars);

#endif
