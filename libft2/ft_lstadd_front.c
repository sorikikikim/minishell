#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new1)
{
	if (lst == NULL || new1 == NULL)
		return ;
	new1->next = *lst;
	*lst = new1;
}
