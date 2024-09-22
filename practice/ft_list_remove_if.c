#include "ft_list.h"
#include <stdlib.h>

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*lst;

	if (!begin_list || !*begin_list)
		return;
	lst = *begin_list;
	if (cmp(lst->data, data_ref) == 0)
	{
		*begin_list = lst->next;
		free(lst);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		lst = *begin_list;
		ft_list_remove_if(&lst->next, data_ref, cmp);
	}
}
