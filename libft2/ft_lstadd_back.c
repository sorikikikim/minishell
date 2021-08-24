#include "libft.h"

void		ft_lstadd_back(t_list **lst, t_list *new1)
{
	t_list	*last;

	if (lst == NULL || new1 == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new1;
		return ;
	}
	last = ft_lstlast(*lst);
	new1->next = last->next;
	last->next = new1;
}
