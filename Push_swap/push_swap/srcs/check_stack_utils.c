#include "../includes/push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->nbr < stack->next->nbr)
			stack = stack->next;
		else
			return (1);
	}
	return (0);
}


int	lst_length(t_stack *stack)
{
	int	len;
	
	len = 0;
	while (stack)
	{
		stack = stack->next;
		len++;
	}
	return (len);
}
