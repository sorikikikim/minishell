#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (0);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
