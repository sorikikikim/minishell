#ifndef UNSET_H
# define UNSET_H
# include "structs.h"
# include "../libft/libft.h"

int	ft_valid_key(char *key);
int ft_unset(t_cmd *cmd_list, char **envp);

#endif
