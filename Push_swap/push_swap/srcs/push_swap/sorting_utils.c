#include "../../includes/push_swap.h"

t_stack	*find_smallest(t_stack *stack)
{
	t_stack	*ret_node;
	long	nbr;
	
	if (!stack)
		return (NULL);
	nbr = LONG_MAX;
	while (stack)
	{
		if (stack->nbr < nbr)
		{
			nbr = stack->nbr;
			ret_node = stack;
		}
		stack = stack->next;
	}
	return (ret_node);
}

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

void	index_cmp(t_stack *stack)
{
	int	i;
	int	median;
	
	i = 0;
	if (!stack)
		return ;
	median = lst_length(stack);
	while (stack)
	{
		stack->index = i;
		if (i <= median)
			stack->above_median = 1;//true
		else
			stack->above_median = 0;//false
		stack = stack->next;
		++i;
	}
}

void	cost_count(t_stack *stack_a, t_stack *stack_b)
{
	int	len_a;
	int	len_b;
	
	len_a = lst_length(stack_a);
	len_b = lst_length(stack_b);
	while (stack_a)
	{
		stack_a->cost = stack_a->index;
		if (stack_a->above_median == 0)
			stack_a->cost = len_a - (stack_a->index);
		if (stack_a->target->above_median == 1)
			stack_a->cost += stack_a->target->index;
		else
			stack_a->cost += len_b - (stack_a->target->index);
		stack_a = stack_a->next;
	}
}

t_stack	*get_cheapest(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}
