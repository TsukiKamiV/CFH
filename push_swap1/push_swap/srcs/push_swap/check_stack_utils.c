#include "../../includes/push_swap.h"

bool	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->nbr > stack->next->nbr)
			return (false);
		stack = stack->next;
	}
	return (true);
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
