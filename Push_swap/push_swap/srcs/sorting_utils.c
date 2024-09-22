#include "../includes/push_swap.h"

t_stack	*find_biggest(t_stack *lst)
{
	long	nb;
	t_stack	*node;
	
	if (!lst)
		return (NULL);
	nb = LONG_MIN;
	node = NULL;
	while (lst)
	{
		if (lst->nbr > nb)
		{
			nb = lst->nbr;
			node = lst;
		}
		lst = lst->next;
	}
	return (node);
}

void	sort_three(t_stack **a)
{
	t_stack	*biggest;
	
	biggest = find_biggest(*a);
	//ft_printf("the biggest number is: %d\n", biggest->nbr);
	if (biggest == *a)
		ra(a);
	else if ((*a)->next == biggest)
		rra(a);
	if ((*a)->nbr > (*a)->next->nbr)
		sa(a);
	
}
