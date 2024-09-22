#include <stdlib.h>
#include "ft_list.h"

t_list	sort_list(t_list *lst, int (*cmp)(int, int))
{
	int	swap;

	t_list	*ret_lst;

	if (!lst || !cmp)
		return (NULL);
	ret_lst = lst;
	while (lst != NULL && lst->next != NULL)
	{
		if ((*cmp)(lst->data, lst->next->data) == 0)
		{
			swap = lst->data;
			lst->data = lst->next->data;
			lst->next->data = swap;
			lst = ret_lst;
		}
		else
			lst = lst->next;
	}
	return (ret_lst);
}
